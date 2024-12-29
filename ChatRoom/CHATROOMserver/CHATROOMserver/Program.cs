using System;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;
using System.Collections.Generic;
using System.Windows;

namespace CHATROOM
{
    public class CHATROOMserver
    {
        List<ChatSocket> clientList = new List<ChatSocket>();

        public static void Main(String[] args)
        {
            CHATROOMserver chatServer = new CHATROOMserver();
            chatServer.run();
        }

        public void run()
        {
            IPEndPoint ipep = new IPEndPoint(IPAddress.Any, ChatSetting.port);

            Socket newsock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            newsock.Bind(ipep);
            newsock.Listen(10);

            while (true)
            {
                Socket socket = newsock.Accept();
                Console.WriteLine("接受一個新連線!");
                ChatSocket client = new ChatSocket(socket);
                try
                {
                    clientList.Add(client);
                    client.newListener(processMsgComeIn);
                }
                catch
                {
                }
                //                clientList.Remove(client);
            }
             //newsock.Close();
        }

        public String processMsgComeIn(String msg)
        {
            Console.WriteLine("收到訊息：" + msg);
            broadCast(msg);
            return "OK";
        }

        public void broadCast(String msg)
        {
            Console.WriteLine("廣播訊息 " + msg + " 線上使用者共" + clientList.Count + "個人!");
            foreach (ChatSocket client in clientList)
            {
                if (!client.isDead)
                {
                    Console.WriteLine("Send to " + client.remoteEndPoint.ToString() + ":" + msg);
                    client.send(msg);
                }
            }
        }
    }
}
