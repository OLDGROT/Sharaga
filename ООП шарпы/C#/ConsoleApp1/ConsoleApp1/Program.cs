using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    //240, 63
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.SetWindowSize(100, 40);
            Console.SetBufferSize(100, 40);

            Console.WriteLine(Console.WindowLeft);
            Console.WriteLine(Console.WindowTop);
            


            

            Console.CursorVisible = true;
            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Green;



            Console.ReadLine();
        }
    }
}
