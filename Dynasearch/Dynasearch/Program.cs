using System;
using System.Linq;

namespace Dynasearch
{
    class Program
    {
        // Example input:
        // 6
        // 3 3 1
        // 1 5 5
        // 1 1 3
        // 5 1 1
        // 1 4 3
        // 5 4 1

        static void Main(string[] args)
        {
            int itemCount = int.Parse(System.Console.ReadLine());

            Task[] tasks = new Task[itemCount];
            for (int i = 0; i < itemCount; ++i)
            {
                var tokens = Console.ReadLine().Split()
                    .Select(int.Parse).Take(3).ToArray();

                int p = tokens[0];
                int w = tokens[1];
                int d = tokens[2];

                tasks[i] = new Task(p, w, d);
            }

            // TODO: randomize or use some better construction algorithm.
            int[] piCurrent = Enumerable.Range(1, itemCount).ToArray();
            int min = int.MaxValue;
            Scheduler scheduler = new Scheduler(tasks);
            bool repeat = true;
            
            while(repeat)
            {
                var beta = scheduler.FindLocalMinimum(piCurrent);
                if(beta.Item2 >= min)
                {
                    repeat = false;
                }
                else
                {
                    min = beta.Item2;
                    piCurrent = beta.Item1;
                }
            }

            Console.WriteLine("pi: {0}", string.Join(", ", piCurrent));
            Console.WriteLine("F(pi): {0}", min);
        }
    }
}
