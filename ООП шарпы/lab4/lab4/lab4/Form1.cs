using System.Diagnostics;

namespace lab4
{
    public partial class Form1 : Form
    {
        public List<string> words = new List<string>();
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            fd.Filter = "text files | *.txt";
            fd.Title = "Выберите файл для чтения";
            fd.ShowDialog();

            Stopwatch sw = new Stopwatch();
            sw.Start();
            string alltext = File.ReadAllText(fd.FileName);
            var allwords = alltext.Split(' ');
            foreach (var word in allwords )
            {
                if (!words.Contains(word))
                    words.Add(word);
            }
            sw.Stop();
            TimeSpan ts = sw.Elapsed;
            textBox1.Text = String.Format("{0} мс.", ts.TotalMilliseconds); 
        }

        private void button2_Click(object sender, EventArgs e)
        {
            
            listBox1.Items.Clear();
            Stopwatch sw = new Stopwatch();
            sw.Start();

            listBox1.BeginUpdate();
            foreach (string str in words)
            {
                if (str.Contains(textBox2.Text))
                    listBox1.Items.Add(str);
            }
            listBox1.EndUpdate();
            sw.Stop();
            TimeSpan ts = sw.Elapsed;
            textBox3.Text = String.Format("{0} мс.", ts.TotalMilliseconds);
        }
    }
}