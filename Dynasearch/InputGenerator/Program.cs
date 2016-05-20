using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InputGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            Random rnd = new Random();

            int iterMax = int.Parse(System.Console.ReadLine());
            int itemCount = int.Parse(System.Console.ReadLine());
            
            int[] periods = Enumerable.Range(1, itemCount).Select(x => rnd.Next(1, 100)).ToArray();
            int[] weights = Enumerable.Range(1, itemCount).Select(x => rnd.Next(1, 10)).ToArray();
            int P = periods.Sum();
            int[] deadlines = Enumerable.Range(1, itemCount).Select(x => rnd.Next(P / 10, 7*P/10 )).ToArray();

            Console.WriteLine(iterMax);
            Console.WriteLine(itemCount);
            for (int i = 0; i < itemCount; ++i)
            {
                Console.WriteLine("{0} {1} {2}", periods[i], weights[i], deadlines[i]);
            }
        }
    }
}
