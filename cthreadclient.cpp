#include "cthreadclient.h"

//====================================================================================================
//глобальные переменные
//====================================================================================================

CThreadClient cThreadClient;//серверный поток

//====================================================================================================
//макроопределения
//====================================================================================================

//порт сервера
#define THREAD_SERVER_PORT 9090
//размер буфера приёма
#define BUFFER_SIZE 16384

//====================================================================================================
//функция потока
//====================================================================================================

UINT ThreadClient(LPVOID pParam)
{
 CThreadClient *cThreadClient_Ptr=reinterpret_cast<CThreadClient*>(pParam);
 if (cThreadClient_Ptr==NULL) return(0);
 cThreadClient_Ptr->Processing(); 
 return(0);
}
//====================================================================================================
//конструктор класса
//====================================================================================================
CThreadClient::CThreadClient(void)
{
 Buffer=new char[BUFFER_SIZE];
 cWinThread_Thread=NULL;
 cDocument_Main_Ptr=NULL;
 WorkingMode=WORKING_MODE_WAIT;
 StuffingEnabled=false;
}
//====================================================================================================
//деструктор класса
//====================================================================================================
CThreadClient::~CThreadClient()
{ 
 Stop();
 delete[](Buffer);
}
//====================================================================================================
//функции класса
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//сохранение массива заданий
//----------------------------------------------------------------------------------------------------
void CThreadClient::SaveTaskVector(char *filename,const vector<CTask> &vector_CTask)
{

}
//----------------------------------------------------------------------------------------------------
//запустить поток
//----------------------------------------------------------------------------------------------------
void CThreadClient::Start(void)
{
 Stop();
 cEvent_Exit.ResetEvent();
 cWinThread_Thread=AfxBeginThread((AFX_THREADPROC)ThreadClient,this);
 cWinThread_Thread->m_bAutoDelete=FALSE;
}
//----------------------------------------------------------------------------------------------------
//остановить поток
//----------------------------------------------------------------------------------------------------
void CThreadClient::Stop(void)
{ 
 if (cWinThread_Thread!=NULL)
 {
  cEvent_Exit.SetEvent();
  WaitForSingleObject(cWinThread_Thread->m_hThread,INFINITE);
  delete(cWinThread_Thread);
  cWinThread_Thread=NULL;    
 }
}
//----------------------------------------------------------------------------------------------------
//задать класс документа
//----------------------------------------------------------------------------------------------------
void CThreadClient::SetDocument(CDocument_Main *cDocument_Main_Set_Ptr)
{
 cDocument_Main_Ptr=cDocument_Main_Set_Ptr;
}
//----------------------------------------------------------------------------------------------------
//основной цикл обработки
//----------------------------------------------------------------------------------------------------
void CThreadClient::Processing(void)
{
 char Host[255];
 sprintf(Host,"127.0.0.1");
 if (cDocument_Main_Ptr!=NULL)
 {
  SClientSettings sClientSettings;
  cDocument_Main_Ptr->GetClientSettings(sClientSettings);
  sprintf(Host,"%i.%i.%i.%i",sClientSettings.ServerIP[0],sClientSettings.ServerIP[1],sClientSettings.ServerIP[2],sClientSettings.ServerIP[3]);
 }
 const long connected_pause_ms=1000;//пауза между подключениями к серверу
 const long wait_pause_ms=1;//пауза между запросами сервера
 while(1)
 {  
  if (WaitForSingleObject(cEvent_Exit.m_hObject,connected_pause_ms)==WAIT_OBJECT_0) break;//получен сигнал на выход
  //подключаемся к серверу
  SOCKET socket_server=INVALID_SOCKET;
  bool on_exit;
  bool is_connected=ConnectAsServer(socket_server,Host,THREAD_SERVER_PORT,on_exit);//подключаемся к серверу
  if (on_exit==true) break;//требуется выйти
  if (is_connected==false) continue;
  //подключение произведено
  vector_Data.clear();
  vector_Data.reserve(MAX_PACKAGE_LENGTH);
  StuffingEnabled=false;
  WorkingMode=WORKING_MODE_GET_CLIENT_PROGRAMM_CRC;
  //выполняем запросы и получение данных от сервера
  on_exit=false;
  while(1)
  {
   if (WaitForSingleObject(cEvent_Exit.m_hObject,wait_pause_ms)==WAIT_OBJECT_0)//получен сигнал на выход
   {
    on_exit=true;
	break;
   }
   if (LinkProcessing(socket_server,on_exit)==false) break;//произошло отключение от сервера
   if (on_exit==true) break;
  }
  //отключаемся от сервера
  //переведём сокет сервера в блокирующий режим
  SetSocketNoBlockMode(socket_server,false);
  //отключаем сервер
  shutdown(socket_server,SD_BOTH);
  closesocket(socket_server);  
  //выходим, если нужно
  if (on_exit==true) break;
  if (cDocument_Main_Ptr!=NULL) cDocument_Main_Ptr->SetOnLine(false);
 }
}
//----------------------------------------------------------------------------------------------------
//обработка обмена с сервером
//----------------------------------------------------------------------------------------------------
bool CThreadClient::LinkProcessing(SOCKET socket_server,bool &on_exit)
{
 const long timeout_us=5000;//таймаут на события

 on_exit=false;
 //анализируем сокеты
 fd_set Readen;
 FD_ZERO(&Readen);//обнуляем список
 fd_set Exeption;
 FD_ZERO(&Exeption);//обнуляем список
 FD_SET(socket_server,&Readen);//добавляем сокет сервера
 FD_SET(socket_server,&Exeption);//добавляем сокет сервера
 //ждём событий в системе
 timeval timeout;
 timeout.tv_sec=0;
 timeout.tv_usec=timeout_us;//таймаут на события
 //спрашиваем, не случилось ли чего с сокетами?
 long ret=select(0,&Readen,0,&Exeption,&timeout);
 if (ret<0)
 {
  on_exit=true;
  return(false);//требуется переподключение
 }
 if (ret>0)
 {
  //не произошло ли исключение на сокете сервера?
  if (FD_ISSET(socket_server,&Exeption)) 
  {
   return(false);//требуется переподключение
  }
  //не пришли ли данные с сервера?
  if (FD_ISSET(socket_server,&Readen))
  {
   //принимаем данные
   long received=recv(socket_server,Buffer,BUFFER_SIZE,0);
   if (received<=0) return(false);//сервер закончил передачу или разрыв соединения
   //анализируем принятые от сервера данные
   NewDataFromServer(socket_server,Buffer,received,on_exit);
   if (on_exit==true) return(true);   
  } 
 }
 //делаем запрос сервера
 if (WorkingMode==WORKING_MODE_GET_CLIENT_PROGRAMM_CRC) return(ExecuteCommand_GetClientProgrammCRC(socket_server,on_exit));//посылаем запрос на контрольную сумму программы на сервере
 if (WorkingMode==WORKING_MODE_AUTORIZATION) return(ExecuteCommand_Autorization(socket_server,on_exit));//посылаем запрос на авторизацию
 if (WorkingMode==WORKING_MODE_CHECK_AUTORIZATION) return(true);//ждём проверки авторизации
 if (WorkingMode==WORKING_MODE_GET_USER_BOOK) return(ExecuteCommand_GetUserBook(socket_server,on_exit));//посылаем запрос на получение базы пользователей
 if (WorkingMode==WORKING_MODE_WAIT_GET_USER_BOOK) return(true);//ждём ответа на запрос на получение базы пользователей
 if (WorkingMode==WORKING_MODE_GET_TASK_BOOK) return(ExecuteCommand_GetTaskBook(socket_server,on_exit));//посылаем запрос на получение базы заданий
 if (WorkingMode==WORKING_MODE_WAIT_GET_TASK_BOOK) return(true);//ждём ответа на запрос на получение базы заданий
 if (WorkingMode==WORKING_MODE_GET_PROJECT_BOOK) return(ExecuteCommand_GetProjectBook(socket_server,on_exit));//посылаем запрос на получение базы проектов
 if (WorkingMode==WORKING_MODE_WAIT_GET_PROJECT_BOOK) return(true);//ждём ответа на запрос на получение базы проектов
 if (WorkingMode==WORKING_MODE_WAIT) 
 {
  if (TaskProcessing(socket_server,on_exit)==false) return(false);
  if (ProjectProcessing(socket_server,on_exit)==false) return(false);
  if (PingProcessing(socket_server,on_exit)==false) return(false);
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//обработка заданий
//----------------------------------------------------------------------------------------------------
bool CThreadClient::TaskProcessing(SOCKET socket_server,bool &on_exit)
{ 
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return(true);
 CTask cTask;
 if (cDocument_Main_Ptr->PopTaskTransferToServer(cTask)==false) return(true);
 SERVER_COMMAND command=SERVER_COMMAND_NOTHING;
 if (cTask.IsMarkForDelete()==true) command=SERVER_COMMAND_DELETED_TASK;
 if (cTask.IsMarkForAdd()==true) command=SERVER_COMMAND_ADDED_TASK;
 if (cTask.IsMarkForChange()==true) command=SERVER_COMMAND_CHANGED_TASK;
 if (command==SERVER_COMMAND_NOTHING) return(true);
 bool ret=cTransceiver_Task.SendTaskDataToServerInPackage(socket_server,cTask,command,cEvent_Exit,on_exit);
 //в случае ошибки возвращаем задание обратно в очередь
 if (ret==false || on_exit==true) cDocument_Main_Ptr->PushTaskTransferToServer(cTask);
 cDocument_Main_Ptr->SaveState();
 if (on_exit==true) return(false);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//обработка проектов
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ProjectProcessing(SOCKET socket_server,bool &on_exit)
{ 
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return(true);
 CProject cProject;
 if (cDocument_Main_Ptr->PopProjectTransferToServer(cProject)==false) return(true);
 SERVER_COMMAND command=SERVER_COMMAND_NOTHING;
 if (cProject.IsMarkForDelete()==true) command=SERVER_COMMAND_DELETED_PROJECT;
 if (cProject.IsMarkForAdd()==true) command=SERVER_COMMAND_ADDED_PROJECT;
 if (cProject.IsMarkForChange()==true) command=SERVER_COMMAND_CHANGED_PROJECT;
 if (command==SERVER_COMMAND_NOTHING) return(true);
 bool ret=cTransceiver_Project.SendProjectDataToServerInPackage(socket_server,cProject,command,cEvent_Exit,on_exit);
 //в случае ошибки возвращаем задание обратно в очередь
 if (ret==false || on_exit==true) cDocument_Main_Ptr->PushProjectTransferToServer(cProject);
 cDocument_Main_Ptr->SaveState();
 if (on_exit==true) return(false);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//обработка сообщений проверки связи
//----------------------------------------------------------------------------------------------------
bool CThreadClient::PingProcessing(SOCKET socket_server,bool &on_exit)
{ 
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return(true);
 if (cDocument_Main_Ptr->GetSendPingAndReset()==false) return(true);
 cTransceiver_Ping.SendPingDataToServerInPackage(socket_server,SERVER_COMMAND_PING,cEvent_Exit,on_exit);
 if (on_exit==true) return(false);
 return(true);
}

//----------------------------------------------------------------------------------------------------
//выполнение команды запроса контрольной суммы программы на сервере
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_GetClientProgrammCRC(SOCKET socket_server,bool &on_exit)
{
 on_exit=false; 
 WorkingMode=WORKING_MODE_WAIT_CLIENT_PROGRAMM_CRC;
 return(cTransceiver_File.GetClientProgrammCRC(socket_server,cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//выполнение команды запроса программы и загрузчика
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_GetClientProgrammAndLoader(SOCKET socket_server,bool &on_exit)
{
 on_exit=false;
 WorkingMode=WORKING_MODE_WAIT_UPDATE;
 return(cTransceiver_File.GetClientProgrammAndLoader(socket_server,cEvent_Exit,on_exit));
}
//----------------------------------------------------------------------------------------------------
//выполнение команды авторизации
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_Autorization(SOCKET socket_server,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr!=NULL) cDocument_Main_Ptr->SetMyParam(false,"","",false);
 CSafeString login="";
 CSafeString password="";
 if (cDocument_Main_Ptr!=NULL)
 {
  SClientSettings sClientSettings;
  cDocument_Main_Ptr->GetClientSettings(sClientSettings);
  login=sClientSettings.Login;
  password=sClientSettings.Password;
 }
 if (cTransceiver_Autorization.SendAutorization(socket_server,login,password,cEvent_Exit,on_exit)==false) return(false);
 WorkingMode=WORKING_MODE_CHECK_AUTORIZATION;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//выполнение команды запроса базы пользователей
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_GetUserBook(SOCKET socket_server,bool &on_exit)
{
 if (cTransceiver_User.GetUserBook(socket_server,cEvent_Exit,on_exit)==false) return(false);
 WorkingMode=WORKING_MODE_WAIT_GET_USER_BOOK;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//выполнение команды запроса базы заданий
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_GetTaskBook(SOCKET socket_server,bool &on_exit)
{
 if (cTransceiver_Task.GetTaskBook(socket_server,cEvent_Exit,on_exit)==false) return(false);
 WorkingMode=WORKING_MODE_WAIT_GET_TASK_BOOK;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//выполнение команды запроса базы проектов
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ExecuteCommand_GetProjectBook(SOCKET socket_server,bool &on_exit)
{
 if (cTransceiver_Project.GetProjectBook(socket_server,cEvent_Exit,on_exit)==false) return(false);
 WorkingMode=WORKING_MODE_WAIT_GET_PROJECT_BOOK;
 return(true);
}

//----------------------------------------------------------------------------------------------------
//приняты данные от сервера
//----------------------------------------------------------------------------------------------------
void CThreadClient::NewDataFromServer(SOCKET socket_server,char *data,unsigned long length,bool &on_exit)
{
 long n;
 on_exit=false;
 SServerAnswer::SHeader sServerAnswer_sHeader; 
 //анализируем принятые данные 
 for(n=0;n<length;n++)
 {
  unsigned char byte=static_cast<unsigned char>(data[n]);
  if (StuffingEnabled==false)//байтстаффинг отключён
  {
   if (byte==PROTOCOL_STUFFING)//включаем байтстаффинг
   { 
    StuffingEnabled=true;
    continue;
   }
   if (byte==PROTOCOL_BEGIN_PACKAGE)//начинаем сборку команды заново
   {
    vector_Data.clear();
    continue;
   }
   if (byte==PROTOCOL_END_PACKAGE)//команда собрана полностью
   {
    sServerAnswer_sHeader=*(reinterpret_cast<SServerAnswer::SHeader*>(&vector_Data[0]));
    //расшифровываем принятые данные
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_CLIENT_PROGRAMM_CRC) ExecuteAnswer_ClientProgrammCRC(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_CLIENT_PROGRAMM_AND_LOADER) ExecuteAnswer_ClientProgrammAndLoader(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_USER_BOOK) ExecuteAnswer_GetUserBook(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_TASK_BOOK) ExecuteAnswer_GetTaskBook(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_PROJECT_BOOK) ExecuteAnswer_GetProjectBook(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_DELETED_USER) ExecuteAnswer_GetDeletedUser(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_ADDED_USER) ExecuteAnswer_GetAddedUser(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_CHANGED_USER) ExecuteAnswer_GetChangedUser(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_DELETED_TASK) ExecuteAnswer_GetDeletedTask(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_ADDED_TASK) ExecuteAnswer_GetAddedTask(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_CHANGED_TASK) ExecuteAnswer_GetChangedTask(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_DELETED_PROJECT) ExecuteAnswer_GetDeletedProject(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_ADDED_PROJECT) ExecuteAnswer_GetAddedProject(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_CHANGED_PROJECT) ExecuteAnswer_GetChangedProject(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_OK) ExecuteAnswer_Ok(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_AUTORIZATION_OK) ExecuteAnswer_AutorizationOk(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
    if (sServerAnswer_sHeader.AnswerID==SERVER_ANSWER_ERROR) ExecuteAnswer_Error(socket_server,static_cast<SERVER_COMMAND>(sServerAnswer_sHeader.CommandID),on_exit);
	if (on_exit==true) return;
    vector_Data.clear();
    continue;
   }
  }
  else//байтстаффинг включён
  {
   if (byte==PROTOCOL_STUFFING_00) byte=0x00;
   if (byte==PROTOCOL_STUFFING_FE) byte=0xFE;
   if (byte==PROTOCOL_STUFFING_FF) byte=0xFF;
   StuffingEnabled=false;
  }
  //добавляем байт в буфер
  vector_Data.push_back(byte);
 }
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение контрольной суммы клиентской программы на сервере
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_ClientProgrammCRC(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 //считываем CRC программы
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 size_t offset=0;
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 unsigned long file_crc16;
 if (cTransceiver_File.ReadCRCInArray(ptr,offset,size,file_crc16)==false) return;

 unsigned short crc16=0;
 char file_name[MAX_PATH];
 GetModuleFileName(NULL,file_name,MAX_PATH);
 FILE *file=fopen(file_name,"rb"); 
 if (file==NULL) return; 

 while(1)
 {  
  unsigned char byte;
  if (fread(&byte,sizeof(unsigned char),1,file)<=0) break;
  crc16^=(byte<<8);
  for (unsigned char i=0;i<8;i++) 
  { 
   if (crc16&0x8000) crc16=(crc16<<1)^0x1021;
                else crc16<<=1;
  }
 }
 fclose(file);
 if (crc16!=file_crc16) ExecuteCommand_GetClientProgrammAndLoader(socket_server,on_exit);//запрашиваем обновление программы  
                   else WorkingMode=WORKING_MODE_AUTORIZATION;//Переходим к авторизации
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение клиентской программы и загрузчика и выполнение обновления
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_ClientProgrammAndLoader(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 size_t offset=0;
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);
 if (cTransceiver_File.ReadClientProgrammAndLoaderInArray(ptr,offset,size)==false) return;
 //перезапускаемся
 if (cDocument_Main_Ptr==NULL) return;
 cDocument_Main_Ptr->RestartWithLoader();
 WorkingMode=WORKING_MODE_AUTORIZATION;
}

//----------------------------------------------------------------------------------------------------
//обработка ответа: получение базы сотрудников
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetUserBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу пользователей
 CVectorUser cVectorUser;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 size_t offset=0;
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);
 while(offset<size)
 {
  CUser cUser;
  if (cTransceiver_User.ReadCUserInArray(ptr,offset,size,cUser)==false) break;
  cUser.SetChangeData(false);
  cVectorUser.AddNew(cUser);
 } 
 cDocument_Main_Ptr->SetUserBook(cVectorUser);
 WorkingMode=WORKING_MODE_GET_TASK_BOOK; 
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение базы заданий
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetTaskBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{ 
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу заданий
 CVectorTask cVectorTask;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 size_t offset=0;
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 while(offset<size)
 {
  CTask cTask;
  if (cTransceiver_Task.ReadCTaskInArray(ptr,offset,size,cTask)==false) break;
  cTask.SetChangeData(false);
  cTask.MarkForWork();
  cVectorTask.PushBack(cTask);
 } 
 cDocument_Main_Ptr->SetTaskBook(cVectorTask);
 WorkingMode=WORKING_MODE_GET_PROJECT_BOOK;
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение базы проектов
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetProjectBook(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{ 
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу заданий
 CVectorProject cVectorProject;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 size_t offset=0;
 SServerAnswer::SHeader *sServerAnswer_sHeader_Ptr=reinterpret_cast<SServerAnswer::SHeader*>(ptr);
 offset+=sizeof(SServerAnswer::SHeader);   
 while(offset<size)
 {
  CProject cProject;
  if (cTransceiver_Project.ReadCProjectInArray(ptr,offset,size,cProject)==false) break;
  cProject.SetChangeData(false);
  cProject.MarkForWork();
  cVectorProject.PushBack(cProject);
 } 
 cDocument_Main_Ptr->SetProjectBook(cVectorProject);
 WorkingMode=WORKING_MODE_WAIT;
}

//----------------------------------------------------------------------------------------------------
//обработка ответа: ок
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_Ok(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (WorkingMode==WORKING_MODE_CHECK_AUTORIZATION)//проверка запроса авторизации
 {
  if (command==SERVER_COMMAND_AUTORIZATION)
  {
   WorkingMode=WORKING_MODE_GET_USER_BOOK;
   return;
  }
  WorkingMode=WORKING_MODE_AUTORIZATION;
 }
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: авторизация принята
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_AutorizationOk(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (WorkingMode==WORKING_MODE_CHECK_AUTORIZATION)//проверка запроса авторизации
 {
  if (command==SERVER_COMMAND_AUTORIZATION)
  {
   size_t size=vector_Data.size();
   char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
   CSafeString guid;
   if (cTransceiver_Autorization.GetAutorizationAnswer(ptr,size,guid)==false) return;
   if (cDocument_Main_Ptr!=NULL) cDocument_Main_Ptr->SetMyParam(true,guid,"",false);
   WorkingMode=WORKING_MODE_GET_USER_BOOK;
   return;
  }
  WorkingMode=WORKING_MODE_AUTORIZATION;
 }
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: ошибка
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_Error(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (command==SERVER_COMMAND_AUTORIZATION)
 {
  if (WorkingMode==WORKING_MODE_CHECK_AUTORIZATION)//была проверка запроса авторизации
  {  
   WorkingMode=WORKING_MODE_AUTORIZATION;
  }
 }

 if (command==SERVER_COMMAND_GET_CLIENT_PROGRAMM_CRC)
 {
  if (WorkingMode==WORKING_MODE_WAIT_CLIENT_PROGRAMM_CRC)//был запрос контрольной суммы программы на сервере
  {
   WorkingMode=WORKING_MODE_AUTORIZATION;
  }
 }


 if (command==SERVER_COMMAND_GET_CLIENT_PROGRAMM_AND_LOADER)
 {
  if (WorkingMode==WORKING_MODE_WAIT_UPDATE)//было ожидание программы с сервера
  {
   WorkingMode=WORKING_MODE_AUTORIZATION;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение данных удалённого сотрудника
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetDeletedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу пользователей
 CUser cUser;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_User.GetUserAnswer(ptr,size,cUser)==false) return;
 cUser.SetChangeData(false);
 cDocument_Main_Ptr->OnDeletedUser(cUser);
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение данных добавленного сотрудника
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetAddedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 CUser cUser;
 //обновляем базу пользователей
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_User.GetUserAnswer(ptr,size,cUser)==false) return;
 cUser.SetChangeData(false);
 cDocument_Main_Ptr->OnAddedUser(cUser);
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение данных изменённого сотрудника
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetChangedUser(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу пользователей
 CUser cUser;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_User.GetUserAnswer(ptr,size,cUser)==false) return;
 cUser.SetChangeData(true);
 cDocument_Main_Ptr->OnChangedUser(cUser);
}

//----------------------------------------------------------------------------------------------------
//обработка ответа: получение данных удалённого задания
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetDeletedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу заданий
 CTask cTask;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Task.GetTaskAnswer(ptr,size,cTask)==false) return;
 cTask.SetChangeData(false);
 cTask.MarkForWork();
 cDocument_Main_Ptr->OnDeletedTask(cTask);
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение данных добавленного задания
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetAddedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу заданий
 CTask cTask;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Task.GetTaskAnswer(ptr,size,cTask)==false) return;
 cTask.SetChangeData(false);
 cTask.MarkForWork();
 cDocument_Main_Ptr->OnAddedTask(cTask);
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение данных изменённого задания
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetChangedTask(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу заданий
 CTask cTask;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Task.GetTaskAnswer(ptr,size,cTask)==false) return;
 cTask.SetChangeData(true);
 cTask.MarkForWork();
 cDocument_Main_Ptr->OnChangedTask(cTask);
}

//----------------------------------------------------------------------------------------------------
//обработка ответа: получение данных удалённого проекта
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetDeletedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу заданий
 CProject cProject;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Project.GetProjectAnswer(ptr,size,cProject)==false) return;
 cProject.SetChangeData(false);
 cProject.MarkForWork();
 cDocument_Main_Ptr->OnDeletedProject(cProject);
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение данных добавленного проекта
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetAddedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу заданий
 CProject cProject;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Project.GetProjectAnswer(ptr,size,cProject)==false) return;
 cProject.SetChangeData(false);
 cProject.MarkForWork();
 cDocument_Main_Ptr->OnAddedProject(cProject);
}
//----------------------------------------------------------------------------------------------------
//обработка ответа: получение данных изменённого проекта
//----------------------------------------------------------------------------------------------------
void CThreadClient::ExecuteAnswer_GetChangedProject(SOCKET socket_server,SERVER_COMMAND command,bool &on_exit)
{
 on_exit=false;
 if (cDocument_Main_Ptr==NULL) return;
 //обновляем базу заданий
 CProject cProject;
 size_t size=vector_Data.size();
 char *ptr=reinterpret_cast<char*>(&vector_Data[0]);
 if (cTransceiver_Project.GetProjectAnswer(ptr,size,cProject)==false) return;
 cProject.SetChangeData(true);
 cProject.MarkForWork();
 cDocument_Main_Ptr->OnChangedProject(cProject);
}


//----------------------------------------------------------------------------------------------------
//подключение к серверу
//----------------------------------------------------------------------------------------------------
bool CThreadClient::ConnectAsServer(SOCKET &socket_server,CSafeString host_name,long port,bool &on_exit)
{
 const long block_timeout_us=500000;//таймаут на повторное соединение

 on_exit=false;
 socket_server=INVALID_SOCKET;
 //подключаемся к серверу
 socket_server=socket(AF_INET,SOCK_STREAM,0);//создаём сокет
 sockaddr_in target;
 target.sin_family=AF_INET;//семество адресов-интернет
 target.sin_port=htons(port);//порт сервера
 u_long addr=inet_addr(host_name);//IP-сервера  
 if (addr==INADDR_NONE)//это не IP
 {
  hostent *host=gethostbyname(host_name); 
  if (host==NULL)
  {
   closesocket(socket_server);
   socket_server=INVALID_SOCKET;
   return(false);//ошибка  
  }
  addr=*((u_long*)host->h_addr_list[0]);
 }
 target.sin_addr.s_addr=addr;
 //переведём сокет в неблокирующий режим
 if (SetSocketNoBlockMode(socket_server,true)==false)
 {
  closesocket(socket_server);
  socket_server=INVALID_SOCKET;
  return(false);//ошибка
 }
 //подключаемся к серверу
 if (WaitForSingleObject(cEvent_Exit.m_hObject,0)==WAIT_OBJECT_0)//получен сигнал на выход
 {
  SetSocketNoBlockMode(socket_server,false);
  closesocket(socket_server);
  socket_server=INVALID_SOCKET;
  on_exit=true;
  return(false);
 }
 if (connect(socket_server,(LPSOCKADDR)&target,sizeof(target))==SOCKET_ERROR)
 {
  int error_code=WSAGetLastError();
  if (error_code==WSAEWOULDBLOCK)
  {
   fd_set Writen;
   FD_ZERO(&Writen);//обнуляем список
   FD_SET(socket_server,&Writen);//добавляем сокет
   timeval timeout;
   timeout.tv_sec=0;
   timeout.tv_usec=block_timeout_us;
   //спрашиваем, нет ли подключения?
   if (select(0,NULL,&Writen,NULL,&timeout)>0)
   {
    return(true);
   }
   else
   {
    //переведём сокет в блокирующий режим
    SetSocketNoBlockMode(socket_server,false);
    closesocket(socket_server);
    socket_server=INVALID_SOCKET;
    return(false);//ошибка
   }
  }
 }
 //подключились
 return(true); 
}

//----------------------------------------------------------------------------------------------------
//задание неблокирующего режима для сокета
//----------------------------------------------------------------------------------------------------
bool CThreadClient::SetSocketNoBlockMode(SOCKET socket_set,bool state)
{
 unsigned long nb=0;
 if (state==true) nb=1;
 if (ioctlsocket(socket_set,FIONBIO,(unsigned long *)&nb)==INVALID_SOCKET) return(false);
 return(true);
}