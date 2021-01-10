using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics; 

namespace Lab_8
{
    public partial class Form1 : Form
    {
        Thread thread_main;
        Thread thread_1;
        Thread thread_2;
        Thread thread_3;
        Font fontHead;
        Font fontBody;
        String head_1;
        String mainThreadData;

        Bitmap pic_paris_rue;
        Bitmap pic_lille;
        Bitmap[] paris_tiles;
        Bitmap[] lille_tiles;

        bool button1 = false;
        bool button2 = false;

        String head_2;
        String osInfo;


        Stopwatch timer_1;
        Stopwatch timer_2;
        bool showMessage = false;  


        public Form1()
        {
            thread_main = Thread.CurrentThread;
            thread_main.Name = "Main Thread";
            fontHead = new Font("Times New Roman", 14, FontStyle.Bold, GraphicsUnit.Pixel);
            fontBody = new Font("Courier New", 12, GraphicsUnit.Pixel);
            head_1 = "Main Thread Information: ";


            paris_tiles = new Bitmap[4];
            lille_tiles = new Bitmap[4];
            pic_paris_rue = new Bitmap("paris_rue.bmp");
            pic_lille = new Bitmap("lille.bmp");

            head_2 = "System Infromatin: ";

            timer_1 = new Stopwatch();
            timer_2 = new Stopwatch(); 

            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void buttonMainInfo_Click(object sender, EventArgs e)
        {
            MainThreadInfo();
            if (!button1)
            {
                button1 = true;
            }
            else
            {
                button1 = false;
                mainThreadData = ""; 
            }

            Invalidate();
        }

        private void buttonPictures_Click(object sender, EventArgs e)
        {
            if (!button2)
            {
                button2 = true;
                showMessage = true; 
                thread_1 = new Thread(new ThreadStart(ThreadPicture_1));
                thread_2 = new Thread(new ThreadStart(ThreadPicture_2));
                thread_3 = new Thread(new ThreadStart(ThreadSystemInfo));
                thread_1.Start();
                thread_2.Start();
                thread_1.Join();
                thread_2.Join();
                thread_3.Start();
                thread_3.Join();
            }
            else
            {
                button2 = false;
                showMessage = false; 
                osInfo = ""; 
            }
            Invalidate();
        }

        private void MainThreadInfo()
        {
            mainThreadData =
            "Name                  : " + thread_main.Name + '\n' +
            "Priority              : " + thread_main.Priority + '\n' +
            "State                 : " + thread_main.ThreadState + '\n' +
            "Is alive              : " + thread_main.IsAlive + '\n' +
            "Is background         : " + thread_main.IsBackground + '\n' +
            "Apartment State       : " + thread_main.ApartmentState + '\n' +
            "Current Culture       : " + thread_main.CurrentCulture + '\n' +
            "Execution Context     : " + thread_main.ExecutionContext + '\n' +
            "Is Thread Pool Thread : " + thread_main.IsThreadPoolThread + '\n' +
            "Managed ThreadId      : " + thread_main.ManagedThreadId;


        }

        private void ThreadPicture_1()
        {
            timer_1.Start(); 
            Graphics dc = CreateGraphics();
            int half_width = pic_paris_rue.Width / 2;
            int hald_height = pic_paris_rue.Height / 2;
            int margin_x = 500;


            for (int i = 0; i < 4; i++)
            {
                paris_tiles[i] = pic_paris_rue.Clone(new Rectangle((i % 2) * half_width, (i / 2) * hald_height, half_width, hald_height), pic_paris_rue.PixelFormat);
            }

            int[] permitation = new int[] { 0, 1, 2, 3 };
            int[] order;
            do
            {
                Random rnd = new Random();
                order = permitation.OrderBy(x => rnd.Next()).ToArray();

                for (int i = 0; i < 4; i++)
                {
                    dc.DrawImage(paris_tiles[order[i]], new Rectangle((i % 2) * half_width + margin_x, (i / 2) * hald_height, half_width, hald_height));
                    Thread.Sleep(10);
                }


            } while (order[0] != 0 | order[1] != 1 | order[2] != 2 | order[3] != 3);

            timer_1.Stop(); 
        }

        private void ThreadPicture_2()
        {
            timer_2.Start(); 
            Graphics dc = CreateGraphics();
            int half_width = pic_lille.Width / 2;
            int hald_height = pic_lille.Height / 2;
            int margin_x = 500;
            int margin_y = 250;


            for (int i = 0; i < 4; i++)
            {
                lille_tiles[i] = pic_lille.Clone(new Rectangle((i % 2) * half_width, (i / 2) * hald_height, half_width, hald_height), pic_lille.PixelFormat);
            }

            int[] permitation = new int[] { 0, 1, 2, 3 };
            int[] order;
            do
            {
                Random rnd = new Random();
                order = permitation.OrderBy(x => rnd.Next()).ToArray();

                for (int i = 0; i < 4; i++)
                {
                    dc.DrawImage(lille_tiles[order[i]], new Rectangle((i % 2) * half_width + margin_x, (i / 2) * hald_height + margin_y, half_width, hald_height));
                    Thread.Sleep(10);
                }


            } while (order[0] != 0 | order[1] != 1 | order[2] != 2 | order[3] != 3);
            timer_2.Stop(); 
        }

        private void ThreadSystemInfo()
        {
            OperatingSystem os = Environment.OSVersion;
            osInfo = "" +
                "Platform              : " + os.Platform + '\n' +
                "Version               : " + os.Version + '\n' +
                "Service Pack          : " + os.ServicePack + '\n' +
                "Version String        : " + os.VersionString + '\n' +
                "MachineName           : " + Environment.MachineName + '\n' +
                "User Name             : " + Environment.UserName + '\n' +
                "OS Version            : "  + Environment.OSVersion + '\n' +
                "SystemPageSize        : " + Environment.SystemPageSize + '\n' +
                "UserInteractive       : " + Environment.UserInteractive + '\n' +
                "TickCount             : " + Environment.TickCount + '\n' +
                "SystemDirectory       : " + Environment.SystemDirectory + '\n' +
                "ProcessorCount        : " + Environment.ProcessorCount + '\n' +
                "ExitCode              : " + Environment.ExitCode + '\n' +
                "HasShutdownStarted    : " + Environment.HasShutdownStarted + '\n' +
                "Is64BitOperatingSystem: " + Environment.Is64BitOperatingSystem + '\n' +
                "Is64BitProcess        : " + Environment.Is64BitProcess; 

        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {

            e.Graphics.DrawString(head_1, fontHead, Brushes.Black, 10, 10);
            e.Graphics.FillRectangle(Brushes.White, 10, 35, 425, 150);
            e.Graphics.DrawString(head_2, fontHead, Brushes.Black, 10, 190);
            e.Graphics.FillRectangle(Brushes.White, 10, 210, 425, 220);

            if (button1)
            {
                e.Graphics.DrawString(mainThreadData, fontBody, Brushes.Black, 10, 35);
            }

            if (button2)
            {
                int half_width = pic_paris_rue.Width / 2;
                int hald_height = pic_paris_rue.Height / 2;
                int margin_x = 500;
                int half_width_2 = pic_lille.Width / 2;
                int hald_height_2 = pic_lille.Height / 2;
                int margin_y = 250;

                for (int i = 0; i < 4; i++)
                {
                    e.Graphics.DrawImage(paris_tiles[i], new Rectangle((i % 2) * half_width + margin_x, (i / 2) * hald_height, half_width, hald_height));
                    e.Graphics.DrawImage(lille_tiles[i], new Rectangle((i % 2) * half_width_2 + margin_x, (i / 2) * hald_height_2 + margin_y, half_width_2, hald_height_2));
                }

                e.Graphics.DrawString(osInfo, fontBody, Brushes.Black, 10, 210);

                long first = timer_1.ElapsedTicks / TimeSpan.TicksPerMillisecond; 
                long second = timer_2.ElapsedTicks / TimeSpan.TicksPerMillisecond;
                e.Graphics.DrawString("First Thread: " + first + "ms", fontBody, Brushes.Black, margin_x, pic_paris_rue.Height + 10);
                e.Graphics.DrawString("Second Thread: " + second + "ms", fontBody, Brushes.Black, margin_x, pic_lille.Height + 10 + margin_y);

                if (showMessage)
                {
                    showMessage = false;
                    if (first < second)
                    {
                        MessageBox.Show("First thread win!");
                    }
                    else
                    {
                        MessageBox.Show("Second thread win!");
                    }
                }
            }
        }
    }
}
