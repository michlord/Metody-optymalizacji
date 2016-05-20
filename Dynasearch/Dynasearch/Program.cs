using System;
using System.Linq;

namespace Dynasearch
{
    class Program
    {
        // Example input (max iter, tasks count, count * (period, weight, deadline)):
        // 5
        // 6
        // 3 3 1
        // 1 5 5
        // 1 1 3
        // 5 1 1
        // 1 4 3
        // 5 4 1

        private static int cost(int[] pi, Task[] tasks)
        {
            int sum  = 0;
            int time = 0;

            for (int i = 0; i < pi.Length; ++i)
            {
                time += tasks[pi[i] - 1].Period;
                sum += time > tasks[pi[i] - 1].Deadline ? tasks[pi[i] - 1].Weight : 0;
            }

            return sum;
        }

        private static Task[] readTasks()
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

            return tasks;
        }

        private static Random rnd = new Random();

        private static int[] randomPi(int itemCount)
        {
            return Enumerable.Range(1, itemCount).OrderBy(item => rnd.Next()).ToArray();
        }

        static void Main(string[] args)
        {
            int    iterMax = int.Parse(System.Console.ReadLine());
                                
            Task[] tasks        = readTasks();
            int    itemCount    = tasks.Length;

            int[]  piCurrent    = randomPi(itemCount);
            int    startingCost = cost(piCurrent, tasks);

            Scheduler scheduler = new Scheduler(tasks);
            int[]     piBest    = (int[]) piCurrent.Clone();
            int       bestCost  = startingCost;


            var watch = System.Diagnostics.Stopwatch.StartNew();
            for (int iter = 0; iter < iterMax; ++iter)
            {
                int  min    = int.MaxValue;
                bool repeat = true;

                while (repeat)
                {
                    var beta = scheduler.FindLocalMinimum(piCurrent);
                    if (beta.Item2 >= min)
                    {
                        repeat = false;
                    }
                    else
                    {
                        min = beta.Item2;
                        piCurrent = beta.Item1;
                    }
                }

                if (min < bestCost)
                {
                    piBest = (int[]) piCurrent.Clone();
                    bestCost = min;
                }

                piCurrent = randomPi(itemCount);
            }
            watch.Stop();
            var elapsedMs = watch.ElapsedMilliseconds;

            int optimizedCost = cost(piBest, tasks);

            Console.WriteLine("|{0,14}|{1,14}|{2,14}|{3,14}|{4,14}|{5,14}|",
                "Tasks", "Starting cost", "Optimized cost", "Improvement", "Iterations", "Time (ms)");
            Console.WriteLine("|{0,14}|{1,14}|{2,14}|{3,14:P2}|{4,14}|{5,14}|",
                itemCount, startingCost, optimizedCost, ((double)(startingCost - optimizedCost) / startingCost), iterMax, elapsedMs);
            Console.WriteLine();
            Console.WriteLine("Optimal pi: {0}", string.Join(", ", piBest));
        }
    }
}
