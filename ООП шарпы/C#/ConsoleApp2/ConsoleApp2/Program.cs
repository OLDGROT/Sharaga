using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.ReadLine();
            Console.WriteLine("Зацени демку");
            Console.Beep(294, 750);
            Console.Beep(350, 750);
            Console.Beep(392, 1000);
            Thread.Sleep(500);
            Console.Beep(294, 750);
            Console.Beep(350, 750);
            Console.Beep(415, 350);
            Console.Beep(392, 1000);
            Thread.Sleep(500);
            Console.Beep(294, 750);
            Console.Beep(350, 750);
            Console.Beep(392, 1000);
            Thread.Sleep(250);
            Console.Beep(350, 750);
            Console.Beep(294, 1000);
            Console.WriteLine("Норм?");
            Console.ReadLine();
        }
    }
}
