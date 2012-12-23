using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int[] time = new int[1000];
            int n = 0;

            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                using (StreamReader sr = new StreamReader(File.Open(openFileDialog1.FileName, FileMode.Open)))
                {
                    while (!sr.EndOfStream)
                    {
                        string[] s = sr.ReadLine().Split(' ');
                        time[n++] = int.Parse(s[1]);
                    }
                }
            }
            Graphics g = pictureBox1.CreateGraphics();
            g.FillRectangle(Brushes.White, new Rectangle(new Point(0, 0), new Size(pictureBox1.Width, pictureBox1.Height)));

            int w = 10, h = 450, l = 3, t = 20000;

            for (int i = 0; i < n - 1; i++)
            {
                g.DrawLine(new Pen(Brushes.Black), new Point(w + i * l, h - (int)(time[i] / t) ), new Point(w + (i + 1) * l, h - (int)(time[i + 1] / t) ));
            }
        }
    }
}
