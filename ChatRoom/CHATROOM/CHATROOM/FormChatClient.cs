using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.IO;

namespace CHATROOM
{
    public partial class FormChatClient : Form
    {
        ChatSocket client;
        StrHandler msgHandler;
        public FormChatClient()
        {
            InitializeComponent();

            msgHandler = this.addMsg;
        }
        public String user()
        {
            return textBox1.Text.Trim();
        }

        public String msg()
        {
            return textBox2.Text;
        }
        /*public String picpath()
        {
            return 
        }
        */
        public void sendMsg()
        {
            if (user().Length == 0)
            {
                MessageBox.Show("請輸入使用者名稱!");
                return;
            }
            if (client == null)
            {
                client = ChatSocket.connect(ChatSetting.serverIp);
                client.newListener(processMsgComeIn);
                client.send(user() + " : 新成員加入!");
                textBox1.Enabled = false;
            }
            if (msg().Length > 0)
            {
                client.send(user() + " : " + msg());
                textBox2.Text = "";
            }
        }

        public String processMsgComeIn(String msg)
        {
            this.Invoke(msgHandler, new Object[] { msg });
            return "OK";
        }
        public String addMsg(String msg)
        {
            string[] words = msg.Split(':');
            string Cmd = words[1].Substring(0, 1);
            string Cmd2 = words[1].Substring(1);
            if (Cmd2 == "picture1")
            { 
                richTextBox1.AppendText(words[0] + " : \n");
                Image image1 =Image.FromFile(System.Environment.CurrentDirectory + @"\images.png");
                Clipboard.SetDataObject(image1);
                richTextBox1.Paste(DataFormats.GetFormat(DataFormats.Bitmap));
                richTextBox1.AppendText("\n");
                return "OK";
            }
            else if (Cmd2 == "picture2")
            {
                richTextBox1.AppendText(words[0] + " : \n");
                Image image1=Image.FromFile(System.Environment.CurrentDirectory + @"\1.png");
                Clipboard.SetDataObject(image1);
                richTextBox1.Paste(DataFormats.GetFormat(DataFormats.Bitmap));
                richTextBox1.AppendText("\n");
                return "OK";
            }
            else
            {
                richTextBox1.AppendText(msg + "\n");
                return "OK";
            }
        }
        private void FormChatClient_Load(object sender, EventArgs e)
        {
            //client.isFile = false;
            //client.path = @"C:\Users\foo\Desktop\CHATROOM";
        }
        private void button1_Click(object sender, EventArgs e)
        {
            sendMsg();
        }
        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '\r')
                sendMsg();
        }
        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            LoadNewPict1();
        }
        public void LoadNewPict1()
        {
            pictureBox2.BackgroundImage = Image.FromFile(System.Environment.CurrentDirectory + @"\images.png");

            pictureBox3.BackgroundImage = Image.FromFile(System.Environment.CurrentDirectory + @"\1.png");
        }
        private void pictureBox2_Click(object sender, EventArgs e)
        {
            textBox2.Text = "picture1";
            sendMsg();
        }
       

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            textBox2.Text = "picture2";
            sendMsg();
        }
     
    }
}       
