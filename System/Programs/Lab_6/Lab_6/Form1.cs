using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_6
{
    public partial class Form1 : Form
    {
        Random random;
        Font btmFont;
        StringFormat stringFormat;


        const string btmName_1 = "Olympic flag";
        const string btmName_2 = "Game";
        const string btmName_3 = "Exit";

        bool flags = false;
        bool game = false;

        Rectangle playingArea;
        Image tic;
        Image tac;
        TextureBrush tBrushTic;
        TextureBrush tBrushTac;
        int coutTimes = 0;
        int[,] gameMatrix;
        bool playerOne = true;

        public Form1()
        {
            stringFormat = new StringFormat();
            stringFormat.Alignment = StringAlignment.Center;
            stringFormat.LineAlignment = StringAlignment.Center;
          
            random = new Random();
            btmFont = new Font("Courier New", 14, FontStyle.Bold, GraphicsUnit.Pixel);

            playingArea = new Rectangle(300, 50, 250, 250);
            tic = new Bitmap(@"C:\Users\Dmitry Chernov\Desktop\Lab_6\Lab_6\x.bmp");
            tac = new Bitmap(@"C:\Users\Dmitry Chernov\Desktop\Lab_6\Lab_6\o.bmp");
            tBrushTic = new TextureBrush(tic, WrapMode.Clamp);
            tBrushTac = new TextureBrush(tac, WrapMode.Clamp);
            gameMatrix = new int[5, 5];

            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void button1_Paint(object sender, PaintEventArgs e)
        {
            drawButton(sender, e, button1, btmName_1);
        }

        private void button2_Paint(object sender, PaintEventArgs e)
        {
            drawButton(sender, e, button2, btmName_2);
        }

        private void button3_Paint(object sender, PaintEventArgs e)
        {
            drawButton(sender, e, button3, btmName_3);
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            button1.Refresh();
            button2.Refresh();
            button3.Refresh();
        }

        private void button1_MouseMove(object sender, MouseEventArgs e)
        {
            Graphics grah = Graphics.FromHwnd(button1.Handle);
            grah.DrawString(btmName_1, btmFont, Brushes.White, button1.ClientRectangle, stringFormat);
        }

        private void button2_MouseMove(object sender, MouseEventArgs e)
        {
            Graphics grah = Graphics.FromHwnd(button2.Handle);
            grah.DrawString(btmName_2, btmFont, Brushes.White, button2.ClientRectangle, stringFormat);
        }

        private void button3_MouseMove(object sender, MouseEventArgs e)
        {
            Graphics grah = Graphics.FromHwnd(button3.Handle);
            grah.DrawString(btmName_3, btmFont, Brushes.White, button2.ClientRectangle, stringFormat);
        }

        private void drawButton(object sender, PaintEventArgs e, Button button, string text)
        {
            Color btmColor_1 = new Color();
            Color btmColor_2 = new Color();

            btmColor_1 = Color.FromArgb(153, 51, 255);
            btmColor_2 = Color.FromArgb(0, 0, 0);

            Point beginPnt = new Point(button.Width / 2, 0);
            Point endPnt = new Point(button.Width / 2, button.Height);
            LinearGradientBrush brush = new LinearGradientBrush(beginPnt, endPnt, btmColor_1, btmColor_2);

            Point beginLine_1 = new Point(button.Width - 20, 0);
            Point endLine_1 = new Point(button.Width, button.Height / 2);
            Point beginLine_2 = new Point(button.Width - 15, 0);
            Point endLine_2 = new Point(button.Width, button.Height / 2 - 5);
            Point beginLine_3 = new Point(button.Width - 10, 0);
            Point endLine_3 = new Point(button.Width, button.Height / 2 - 10);
            Pen pen = new Pen(Color.Coral, 2);

            e.Graphics.FillRectangle(brush, 0, 0, button.Width, button.Height);
            e.Graphics.DrawString(text, btmFont, Brushes.Black, button.ClientRectangle, stringFormat);
            e.Graphics.DrawLine(pen, beginLine_1, endLine_1);
            e.Graphics.DrawLine(pen, beginLine_2, endLine_2);
            e.Graphics.DrawLine(pen, beginLine_3, endLine_3);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!flags)
            {
                flags = true;
                game = false;
                Invalidate();
            }
            else
            {
                flags = false;
                Invalidate();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!game)
            {
                game = true;
                flags = false;
                playerOne = true; 
                Invalidate();
                Array.Clear(gameMatrix, 0, gameMatrix.Length);
            }
            else
            {
                game = false;
                Invalidate();
                Array.Clear(gameMatrix, 0, gameMatrix.Length);
            }
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            if (flags)
            {
                //Lower Rings
                //Yellow
                e.Graphics.DrawEllipse(new Pen(Color.FromArgb(251, 177, 50), 5), 355, 160, 100, 100);
                //Green 
                e.Graphics.DrawEllipse(new Pen(Color.FromArgb(28, 139, 60), 5), 470, 160, 100, 100);

                //Upper Rings
                //Red
                e.Graphics.DrawArc(new Pen(Color.FromArgb(237, 51, 78), 5), 520, 110, 100, 100, 182, 355);
                // Black Upper
                e.Graphics.DrawArc(new Pen(Color.FromArgb(0, 0, 0), 5), 410, 110, 100, 100, 183, 253);
                //Black Lower
                e.Graphics.DrawArc(new Pen(Color.FromArgb(0, 0, 0), 5), 410, 110, 100, 100, 82, 95);
                //Blue
                e.Graphics.DrawArc(new Pen(Color.FromArgb(8, 133, 194), 5), 295, 110, 100, 100, 82, 353);
            }

            if (game)
            {
                Pen pen = new Pen(Color.Black, 2);
                e.Graphics.FillRectangle(Brushes.White, playingArea);
                for (int i = 0; i < 6; ++i)
                {
                    e.Graphics.DrawLine(pen, 50 * i + 1 + 300, 50, 50 * i + 1 + 300, 300);
                    e.Graphics.DrawLine(pen, 300, 50 * i + 1 + 50, 550, 50 * i + 1 + 50);
                }
            }

            if (playerOne & game)
            {
                e.Graphics.DrawString("Player 1 is choosing!", btmFont, Brushes.Black, new Point(300, 0));
            }
            else if (!playerOne & game)
            {
                e.Graphics.DrawString("Player 2 is choosing!", btmFont, Brushes.Black, new Point(300, 0));
            }
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            Point mouse = new Point(e.X, e.Y);
            Graphics graph = this.CreateGraphics();
            int left = ((mouse.X) / 50) * 50;
            int top = ((mouse.Y) / 50) * 50;
            int i = ((mouse.X - 300) / 50);
            int j = ((mouse.Y - 50) / 50);
            Color color_1 = new Color();
            Color color_2 = new Color();
            color_1 = Color.FromArgb(80, random.Next(255), random.Next(255), random.Next(255));
            color_2 = Color.FromArgb(80, random.Next(255), random.Next(255), random.Next(255));
            LinearGradientBrush brush = new LinearGradientBrush(new Point(0, 0), new Point(50, 0), color_1, color_2);

            if (playingArea.Left < mouse.X & mouse.X < playingArea.Right &
                playingArea.Top < mouse.Y & mouse.Y < playingArea.Bottom)
            {
                if (coutTimes == 25)
                {
                    coutTimes = 0;
                    MessageBox.Show("All cells are full! Try again!");
                    Invalidate();
                    Array.Clear(gameMatrix, 0, gameMatrix.Length);
                    playerOne = true;
                }
                else if (gameMatrix[i, j] == 0)
                {
                    if (playerOne)
                    {
                        graph.FillRectangle(brush, left + 2, top + 2, 48, 48);
                        tBrushTic.TranslateTransform(left + 2, top + 2);
                        graph.FillRectangle(tBrushTic, left + 2, top + 2, 48, 48);
                        tBrushTic.TranslateTransform(-(left + 2), -(top + 2));
                        playerOne = false;
                        Invalidate(new Region(new Rectangle(300, 0, 100, 50)), true);
                        gameMatrix[i, j] = 1;
                        coutTimes++;
                    }
                    else
                    {
                        graph.FillRectangle(brush, left + 2, top + 2, 48, 48);
                        tBrushTac.TranslateTransform(left + 2, top + 2);
                        graph.FillRectangle(tBrushTac, left + 2, top + 2, 48, 48);
                        tBrushTac.TranslateTransform(-(left + 2), -(top + 2));

                        playerOne = true;
                        Invalidate(new Region(new Rectangle(300, 0, 100, 50)), true);
                        gameMatrix[i, j] = 2;
                        coutTimes++;
                    }

                    int answer = gameDraw();
                    if (answer != 0)
                    {
                        if (answer == 1)
                        {
                            MessageBox.Show("Player 1 wins !");
                            coutTimes = 0;
                            Array.Clear(gameMatrix, 0, gameMatrix.Length);
                            Invalidate();
                            playerOne = true;
                        }

                        if (answer == 2)
                        {
                            MessageBox.Show("Player 2 wins !");
                            coutTimes = 0;
                            Array.Clear(gameMatrix, 0, gameMatrix.Length);
                            Invalidate();
                            playerOne = true;
                        }
                    }
                }
            }
        }

        private int gameDraw()
        {
            int answer = 0;

            for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 2; ++j)
                if (gameMatrix[i, j] > 0)
                {
                    int k = j + 1;
                    while (k < 5 && gameMatrix[i, k] == gameMatrix[i, j] && answer == 0)
                    {
                        if (k - j == 3)
                            answer = gameMatrix[i, j];
                        k++;
                    }
                }

            for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 5; ++j)

                if (gameMatrix[i, j] > 0)
                {
                    int k = i + 1;
                    while (k < 5 && gameMatrix[k, j] == gameMatrix[i, j] && answer == 0)
                    {
                        if (k - i == 3)
                            answer = gameMatrix[i, j];
                        k++;
                    }
                }

            return answer;
        }
    }
}