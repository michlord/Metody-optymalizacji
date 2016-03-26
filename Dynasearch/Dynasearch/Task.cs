using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dynasearch
{
    struct Task
    {
        private readonly int period;
        private readonly int weight;
        private readonly int deadline;

        public int Period { get { return period; } }
        public int Weight { get { return weight; } }
        public int Deadline { get { return deadline; } }

        public Task(int period, int weight, int deadline)
        {
            this.period = period; this.weight = weight; this.deadline = deadline;
        }

        public override string ToString()
        {
            return string.Format("{0},{1},{2}", Period, Weight, Deadline);
        }
    }
}
