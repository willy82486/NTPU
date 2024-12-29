using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;
using System.Windows;
using System.Windows.Forms;

namespace CHATROOM
{
    public class ChatSetting    
    {
        public static String serverIp = "192.168.0.11";
        public static int port = 3766;
    }

    public delegate String StrHandler(String str);

    public class ChatSocket
    {
        public Socket socket;
     //   public bool isFile;
     //   public string path;
     //   public DirectoryInfo di;
     //   public string File_name;
        public NetworkStream stream;
        public StreamReader reader;
        public StreamWriter writer;
        public StrHandler inHandler;
        public EndPoint remoteEndPoint;
        public bool isDead = false;

        public ChatSocket(Socket s)
        {
            socket = s;
            stream = new NetworkStream(s);
            reader = new StreamReader(stream);
            writer = new StreamWriter(stream);
            remoteEndPoint = socket.RemoteEndPoint;
        }

        public String receive()
        {   
            return reader.ReadLine();
        }

           public ChatSocket send(String line)
           {
               writer.WriteLine(line);
               writer.Flush();
               return this;
           }
        

        /*public void send(String Msg)
        {
            byte[] Byte = Encoding.UTF8.GetBytes(Msg);
            try
            {
                socket.Send(Byte, 0, Byte.Length, SocketFlags.None);
            }
            catch (Exception a)
            {
                MessageBox.Show("Client Send\n" + a.Message);
                return;
            }
        }*/
        public static ChatSocket connect(String ip)
        {
            IPEndPoint ipep = new IPEndPoint(IPAddress.Parse(ip), ChatSetting.port);

            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Connect(ipep);
            return new ChatSocket(socket);
        }

        public Thread newListener(StrHandler pHandler)
        {
            inHandler = pHandler;

            Thread listenThread = new Thread(new ThreadStart(listen));
            listenThread.Start();
            return listenThread;
        }

        public void listen()
        {
            try
            {
                while (true)
                {
                    String line = receive();
                    inHandler(line);
                }
            }
            catch (Exception e)
            {
                isDead = true;
                MessageBox.Show(e.Message);
                Console.WriteLine(e.Message);
            }
        }
 
    }
}

