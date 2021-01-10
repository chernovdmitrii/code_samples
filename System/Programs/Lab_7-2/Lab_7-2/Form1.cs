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
using System.Drawing.Drawing2D;

namespace Lab_7_2
{
    public partial class Form1 : Form
    {
        //Global variables
        Bitmap pic_paris;
        Bitmap pic_paris_rue;
        Bitmap pic_lille;
        Bitmap pic_biarritz; 
        string france_path;
        int count = 0;
        Font btmFont;
        
        public Form1()
        {
            france_path = Application.StartupPath + "\\France";
            pic_paris = new Bitmap(france_path + "\\paris.bmp");
            pic_paris_rue = new Bitmap(france_path + "\\paris_rue.bmp");
            pic_lille = new Bitmap(france_path + "\\lille.bmp");
            pic_biarritz = new Bitmap(france_path + "\\biarritz.bmp");

            btmFont = new Font("Courier New", 14, FontStyle.Bold, GraphicsUnit.Pixel);
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void buttonPrev_Click(object sender, EventArgs e)
        { 


            if (count < 5)
            {
                count -= 1;
            }
            if (count == 5)
            {
                count = 1;
            }
            if (count <= 0)
            {
                count = 4;
            }

            drawPersentation(count);
           //Invalidate();
        }

        private void buttonNext_Click(object sender, EventArgs e)
        {
            if (count <= 5)
            {
                count += 1;
            }
            if (count == 5)
            {
                count = 1;
            }
            drawPersentation(count);
            //Invalidate();
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            count = 0;
            Invalidate();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            
        }

        private void drawPersentation(int _count)
        {
            string text = ""; 
            switch (_count)
            {
                case 0:
                    Console.WriteLine(count);
                    break;
                case 1:
                    text = "Vue de Paris de la fenêtre";
                    drawSlide(pic_paris, text);
                    Console.WriteLine(count);
                    break;
                case 2:
                    text = "Passage piéton parisien avec le feu rouge"; 
                    drawSlide(pic_paris_rue, text);
                    Console.WriteLine(count);
                    break;
                case 3:
                    text = "Entrée du night club"; 
                    drawSlide(pic_lille, text);
                    Console.WriteLine(count);
                    break;
                case 4:
                    text = "La phare de Biarritz"; 
                    drawSlide(pic_biarritz, text);
                    Console.WriteLine(count);
                    break;
                default:
                    break;
            }
        }

        private void drawSlide(Bitmap slide, string text)
        {
            Graphics dc = this.CreateGraphics();
           

            for (int i = 100; i > 1; i--)
            {
                //this.Refresh();
                Thread.Sleep(50);
                dc.FillRectangle(Brushes.White, 0, 0, 700, 700);
                dc.DrawImage(slide, 20 + i * 4, 10, slide.Width / 3, slide.Height / 3);
                Point pos = new Point(20 + i * 4, 10 + slide.Height / 3); 
                dc.DrawString(text, btmFont, Brushes.Black, pos) ;
            }
        }
    }
}
