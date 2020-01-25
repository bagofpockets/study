using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pr3_5._2
{
    class Program
    {
        static void Main(string[] args)
        {
            const double Q = 9;
            int K, N;
            double P = 1;
            Console.Write("Строки: ");
            K = Convert.ToInt32(Console.ReadLine()) + 1;
            Console.Write("Столбцы: ");
            N = Convert.ToInt32(Console.ReadLine()) + 1;

            double[] arr = new double[K];
            var watch = System.Diagnostics.Stopwatch.StartNew();

            Parallel.For(1, K, (i) =>
            {
                arr[i] = Math.Sqrt((Q * i) / 100);
                //Console.Write("{0}\t", arr[i]);
                //Console.WriteLine();
                P *= (N - 1) * arr[i];
            });

            watch.Stop();

            Console.Write("{0}\n", "П = " + P);
            Console.Write("{0}\n", "Время " + watch.ElapsedTicks.ToString());
            Console.Read();
        }
    }
}