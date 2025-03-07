#include "StdAfx.h"
#include "ServerWork.h"
#include "DBWork.h"

#define SIZE 4048         // Размер принимаемого сообщения
 
void CTemp::temp(){}
 int Port;
 User *user;
 CListBox *ListBox;
 WSADATA WSAData;           // Структура конфигурации DLL
 SOCKET WinSocket;          // Наш сокет
 sockaddr_in SockStruct;    // Структура содержит информацию о сокете
 int Bind;                  // Хранит результат связывания локального сетевого адреса с сокетом
 int Listen;                // Хранит результат прослушивания сокета
 int Connect;               // Переменная хранит результат подключения клиента к серверу
 int Send;                  // Переменная хранит результат отправки сообщения
 int Recv;                  // Переменная хранит результат приема сообщения
 unsigned int  Q;                     // Определяем количество одновременно работающих клиентов
 CString List;
 CDBWork DBWork;
HANDLE hMainThread;        // Дескриптор основного потока
HANDLE hGetMes;             // Дескриптор функции, определяющей тип сообщения*/
bool created=false;
 void WINAPI ParserServer(int n);
 DWORD WINAPI MainThread();

bool CreateMainThread(CListBox *OutPut)
{
	if(created==false)
	{
	  DWORD id;
	  ListBox=OutPut;
      hMainThread = CreateThread(NULL,
                             0,
                             (LPTHREAD_START_ROUTINE)MainThread,
                             NULL,
                             0,
	                         &id);
	 created=true;
	 return true;
	}
	return false;
	
}
void WINAPI ParserServer(int n)  //n- номер пользователя
{
      // Буфер входящих данных
  char *Buffer=new char[SIZE];

  // Запускаем бесконечный цикл приема сообщений
 while (true)
 {
    // Делаем так, чтобы не было мусора во входящих данных
    for (int i=0; i<SIZE; i++)
      Buffer[i] = '\0';

    // Получаем данные
    Recv = recv(user[n].Accept, Buffer, SIZE, 0);
      // Начальные данные для передачи нового списка
	CString f=CString(Buffer);
	if(f!="")
	{
	  f.Insert(0,">>  ");
	  ListBox->AddString(f);
	  
	 /* CDBWork::TFieldValue add;
         add.R=f;
		 DBWork.writeDB(add);
*/
	  f+="\n";
	 // File.WriteString((LPCSTR)f);
	}
	/*List = "2";
      List += Form1->Edit4->Text;
      List += "#";
      */
	//if (Recv == SOCKET_ERROR)
 }
    // Если сокет отключен
 /*   if (Recv == SOCKET_ERROR)
    {
      // Начальные данные для передачи нового списка
      List = "2";
      List += Form1->Edit4->Text;
      List += "#";
      // Обозначаем, что клиент отключился
      user[n].active = false;
      // Очищаем список
      Form1->ListBox1->Items->Clear();

      // Обновляем список всех подключенных клиентов
      for (int i=0; i<Q; i++)
        if (user[i].active == true)
          Form1->ListBox1->Items->Add(user[i].Nick);

      // Собираем новый список подключенных клиентов
      for (int i=0; i<Q; i++)
        if (user[i].active == true)
        {
          List += user[i].Nick;
          List += "#";
        }

      // Рассылаем собранный список всем подключенным клиентам
      for (int i=0; i<Q; i++)
        if (user[i].active == true)
          send(user[i].Accept, List.c_str(), List.Length() + 1, 0);

      // Завершаем поток отключившегося клиента
      CloseHandle(user[n].hRecv);
      // Закрываем сокет отключившегося клиента
      closesocket(user[n].Accept);

      Form1->Memo1->Lines->Add("Пользователь '" + user[n].Nick + "' вышел из сети...");
      Form1->Memo1->Lines->Add("");

      if (Form1->ListBox1->Items->Count == 0)
        Form1->Button7->Enabled = false;

      // Завершаем цикл while
      break;
    }
    // Если сокет принял сообщение
    else
    {
      // Пришло сообщение
      if (Buffer[0] == '1')
      {
        AnsiString From = "";
        AnsiString To = "";
        AnsiString Message = Buffer;
        Message = Message.Delete(1,1);
        AnsiString Text = "";

        // Найденное количество служебных символов в сообщении
        int k = 0;

        for (int i=1; i<strlen(Buffer); i++)
          if (Message[i] == '#')
            k++;
          else
            if (k == 0)
              From += Message[i];
            else
              if (k == 1)
                To += Message[i];
              else
                if (k == 2)
                  Text += Message[i];

        // Проверка предназначения сообщения
        // Если пришло для сервера
        if (To == Form1->Edit4->Text)
        {
          Form1->Memo1->Lines->Add("Сообщение от '" + From + "':");
          Form1->Memo1->Lines->Add(Text);
          Form1->Memo1->Lines->Add("");
        }
        // Если пришло не для сервера
        else
        {
          for (int i=0; i<Q; i++)
            if (user[i].Nick == To)
              Send = send(user[i].Accept, Buffer, strlen(Buffer) + 1, 0);
        }
      }


      // Пришел ник пользователя
      if (Buffer[0] == '6')
      {
        // Получаем ник клиента от только что подключенного клиента
        AnsiString Nick = "";
        Nick = Buffer;
        Nick = Nick.Delete(1,1);
        user[n].Nick = Nick;

        // Начальные условия для посылки обновленного списка
        List = "2";
        List += Form1->Edit4->Text;
        List += "#";

        // собираем список контактов для отсылки клиентам
        for (int i=0; i<Q; i++)
          if (user[i].active == true)
          {
            List += user[i].Nick;
            List += "#";
          }

        // Очищаем список для вывода нового списка контактов
        Form1->ListBox1->Clear();

        // Выводим всех подключенных клиентов
        for (int i=0; i<Q; i++)
          if (user[i].active == true)
            Form1->ListBox1->Items->Add(user[i].Nick);

        // отсылаем список контактов всем активным клиентам
        for (int i=0; i<Q; i++)
          if (user[i].active == true)
            send(user[i].Accept, List.c_str(), List.Length() + 1, 0);

        Form1->Memo1->Lines->Add("Пользователь '" + user[n].Nick + "' вошел в сеть...");
        Form1->Memo1->Lines->Add("");

        if (Form1->ListBox1->Items->Count > 0)
        {
          Form1->Button1->Enabled = true;
          Form1->Button7->Enabled = true;
        }
        else
        {
          Form1->Button1->Enabled = false;
          Form1->Button7->Enabled = true;
        }
      }
    }
  }
  */

}
////////////////////////////////////****************************////////////////////////////////////
void Stop()
{
  /*  int code1=1;
    int code2=2;

    for (int i=0; i<Q; i++)
      if (user[i].active == true)
      {
		  hRecv[i]
     //   TerminateThread(hRecv[i], code1);
        closesocket(user[i].Accept);
      }

    TerminateThread(hMainThread, code2);
    closesocket(WinSocket);*/
   
}
////////////////////////////////////****************************////////////////////////////////////
DWORD WINAPI MainThread()
{
 CString Message;
 unsigned int i;
 ListBox->AddString("");
 ListBox->AddString(">> Начало работы программы...");
 if (WSAStartup(MAKEWORD(2,1), &WSAData) != 0)
 {
	ListBox->AddString(">> Ошибка! Невозможно инициализировать библиотеку сокетов! Функция MainThread()");
    return false;
 }
 // Создаем сокет
 WinSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 if (WinSocket == SOCKET_ERROR)
 {
    ListBox->AddString(">> Ошибка!  Невозможно создать сокет! Функция MainThread()");
	return false;
 }
 // Заполняем поля структуры для сокета
 SockStruct.sin_family = AF_INET;
 SockStruct.sin_port = Port;
 SockStruct.sin_addr.s_addr = INADDR_ANY; 
// Связываем локальный сетевой адрес с сокетом
 Bind = bind(WinSocket, (sockaddr*)&SockStruct, sizeof(SockStruct));
 if (Bind == SOCKET_ERROR)
 {
    ListBox->AddString(">> Ошибка! Невозможно связать локальный сетевой адрес с сокетом! Функция MainThread()");
	return false;
 }
// Ставим подключаемых клиетов в очередь
 Listen = listen(WinSocket, 5);
 if (Listen == SOCKET_ERROR)
 {
    ListBox->AddString(">> Ошибка! Невозможно связать локальный сетевой адрес с сокетом! Функция MainThread()");
	return false;
 }
 Message.Format(">> Серверное приложение запущено. Выполняется прослушивание порта %d ...",Port);
 ListBox->AddString((LPCSTR)Message);
// Начальные условия для всех клиентов
  for (i=0; i<Q; i++)
  {
        user[i].active = false;
        user[i].size = sizeof(user[i].AcpStruct);
        user[i].IP = "";
//        user[i].Nick = "";
  }
  // Ставим подключаемых клиетов в очередь
  int num = 0; // переменная хранит номер свободного клиента
  List = "";
   while (true)
   {
              for (int i=Q; i>0; i--)
                if (user[i].active == false)
                  num = i;

              user[num].Accept = accept(WinSocket, (sockaddr*)&user[num].AcpStruct, (int*)&user[num].size);
              if (user[num].Accept == SOCKET_ERROR)
              {
              /*  Form1->Memo1->Lines->Add("ОШИБКА: Невозможно принять входящее подключение!");
                Form1->Memo1->Lines->Add("");*/
              }
              else
              {
                // Устанавливаем флаг того, что клиент подключен
                user[num].active = true;

                // запуск потока клиента
/*                user[num].hRecv = CreateThread(NULL,
                                               0,
                                               (LPTHREAD_START_ROUTINE)ParserServer,
                                               (void*)num,
                                               0,
                                               &user[num].id);*/
			  }
     }
  /*  

      {
    
        else
        {
          // Ставим подключаемых клиетов в очередь


            int num = 0; // переменная хранит номер свободного клиента
            List = "";

            // Запускаем бесконечный цикл подключения клиентов
            while (true)
            {
              for (int i=Q; i>0; i--)
                if (user[i].active == false)
                  num = i;

              user[num].Accept = accept(WinSocket, (sockaddr*)&user[num].AcpStruct, (int*)&user[num].size);
              if (user[num].Accept == SOCKET_ERROR)
              {
                Form1->Memo1->Lines->Add("ОШИБКА: Невозможно принять входящее подключение!");
                Form1->Memo1->Lines->Add("");
              }
              else
              {
                // Устанавливаем флаг того, что клиент подключен
                user[num].active = true;

                // запуск потока клиента
                user[num].hRecv = CreateThread(NULL,
                                               0,
                                               (LPTHREAD_START_ROUTINE)ParserServer,
                                               (void*)num,
                                               0,
                                               &user[num].id);

              }
            }
          }
        }
      }
    }
*/
  return true;
}

/*******************************************************************************/
/* Ôóíêöèÿ âûõîäà èç ïðîãðàììû                                                */
/******************************************************************************/
void Exit()
{
 /*   int code1;
    int code2;

    for (unsigned int i=0; i<Q; i++)
      if (user[i].active == true)
      {
//        TerminateThread(user[i].hRecv, code1);
//        CloseHandle(user[i].hRecv);
        closesocket(user[i].Accept);
      }

    TerminateThread(hMainThread, code2);
    CloseHandle(hMainThread);
    closesocket(WinSocket);
*/
}

////////////////////////////////////****************************////////////////////////////////////

