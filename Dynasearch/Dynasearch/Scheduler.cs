using System;
using System.Linq;

namespace Dynasearch
{
    class Scheduler
    {
        private int n;                 // 3

        private int[] pi;              // {3,1,2}
        private readonly Task[] tasks; // {1:(3,8,3),2:(2,4,10),3:(1,10,1)}
        private int[] completionTimes; // {0, 1, 4, 6}

        private int[] dp;              // {0, 3, 0, 0}
        private int[] dpSwaps;

        public Scheduler(Task[] tasks)
        {
            n = tasks.Length;
            this.tasks = (Task[])tasks.Clone();
        }

        // Takes some permutation and returns a tuple with
        //  - a permutation that has minimum objective function
        //  - the value of the function
        public Tuple<int[], int> FindLocalMinimum(int[] pi)
        {
            this.pi = (int[])pi.Clone();

            DpInit();
            DpAlgorithm();
            DpCreatePi();

            return new Tuple<int[], int>(this.pi, dp[n]);
        }

        private int Pi(int j)
        {
            return pi[j - 1];
        }

        private int Deadline(int j)
        {
            return tasks[j - 1].Deadline;
        }

        private int Weight(int j)
        {
            return tasks[j - 1].Weight;
        }

        private int Period(int j)
        {
            return tasks[j - 1].Period;
        }

        private int Cost(int j, int time)
        {
            return time > Deadline(j) ? Weight(j) : 0;
            // Congram version:
            // return time > Deadline(j) ? Weight(j) * (time - Deadline(j)) : 0;
        }

        private void DpInit()
        {
            completionTimes = new int[n + 1];
            completionTimes[0] = 0;
            for (int i = 1; i <= n; ++i)
            {
                completionTimes[i] += completionTimes[i - 1] + Period(Pi(i));
            }

            dp = new int[n + 1];
            dp[0] = 0;
            dp[1] = Cost(Pi(1), completionTimes[1]);

            dpSwaps = new int[n + 1];
            dpSwaps[0] = 0;
            dpSwaps[1] = 1;
        }

        private void DpAlgorithm()
        {
            for (int j = 2; j <= n; ++j)
            {
                int min = dp[j - 1] + Cost(Pi(j), completionTimes[j]);
                int swap = j;

                for (int i = 0; i <= j - 2; ++i)
                {
                    int val = dp[i] + Cost(Pi(j), completionTimes[i] + Period(Pi(j)))
                        // sum for k from i+2 to j-1 (there should be total j-i-2 elements in the sum)
                        + Enumerable.Range(i + 2, j - i - 2).Sum(k => Cost(Pi(k), completionTimes[k] + Period(Pi(j)) - Period(Pi(i + 1))))
                        + Cost(Pi(i + 1), completionTimes[j]);

                    if(val < min)
                    {
                        min = val;
                        swap = i + 1;
                    }
                }

                dp[j] = min;
                dpSwaps[j] = swap;
            }
        }

        private void DpCreatePi()
        {
            for (int i = n; i >= 1; --i)
            {
                if (dpSwaps[i] != i)
                {
                    int tmp = pi[i - 1];
                    pi[i - 1] = pi[dpSwaps[i] - 1];
                    pi[dpSwaps[i] - 1] = tmp;
                    i = dpSwaps[i];
                }
            }
        }

    }
}
