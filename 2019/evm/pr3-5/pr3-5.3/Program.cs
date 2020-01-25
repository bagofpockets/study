using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace pr3_5._3
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

            Thread thrd1 = new Thread(Thread1);
            void Thread1()
            {
                for (int i = 1; i < (K) / 2; i++)
                {
                    arr[i] = Math.Sqrt((Q * i) / 100);
                    //Console.Write("{0}\t", arr[i]);
                    //Console.WriteLine();
                    P *= N * arr[i];
                    Thread.Sleep(0);
                };
            }

            Thread thrd2 = new Thread(Thread2);
            void Thread2()
            {
                for (int i = K / 2; i < K ; i++)
                {
                    arr[i] = Math.Sqrt((Q * i) / 100);
                    //Console.Write("{0}\t", arr[i]);
                    //Console.WriteLine();
                    P *= N * arr[i];
                    Thread.Sleep(0);
                };
            }

            var watch = System.Diagnostics.Stopwatch.StartNew();
            thrd1.Start();
            thrd2.Start();
            watch.Stop();
            thrd1.Join();
            thrd2.Join();
            Console.Write("{0}\n", "П = " + P);
            Console.Write("{0}\n", "Время " + watch.ElapsedTicks.ToString());
            Console.Read();
        }
    }
}