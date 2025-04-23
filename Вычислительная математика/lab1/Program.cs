using System;
using System.Text;


class Program
{
    static void Main()
    {
        //Func<double, double> f = x => -4 * x + 3 * Math.Pow(x, 2.0 / 3.0) + 4.1 * Math.Pow(x, 2) - 15.61; // Функция
        Func<double, double> f = x => -4 * x + 3 * Math.Cbrt(Math.Pow(x, 2.0)) + 4.1 * Math.Pow(x, 2) - 15.61; // Уравнение
        Func<double, double> foo = x => (4 - 3 / (Math.Cbrt(x)) + 15.61 / (x)) / 4.1;
        Func<double, double> df = x => 8.2 * x + 2 / Math.Cbrt(x) - 4; // Производная для метода Ньютона
        Func<double, double> ddf = x => -(2 / 3) / (Math.Cbrt(Math.Pow(x, 4.0))) + 8.2;
        //Func<double, double> phi = x => Math.Pow(x + 2, 1.0 / 3.0); // Функция для метода простых итераций


        Func<double, double> maks = x => 5 * Math.Sin(x) - x;
        Func<double, double> dmaks = x => -5 * Math.Cos(x) - 1;

        double maksLeft = Math.PI/18;
        double maksRight = 5*Math.PI/18;



        //Func<double, double> dfooo = x => -4 - 2/Math.Cbrt(Math.Abs(x))+8.2*x;
        Func<double, double> F = x => x - f(x)/(-17.27);


        // фукнция где выразили 3 икс в 2/3 степени
        // эта функция плохая потому что берется квадрат из отрицательного числа (
        //Func<double, double> func1 = x => 8 / (3 * Math.Sqrt(3)) * Math.Sqrt(Math.Pow(x, 3)) - 41 / 30 * Math.Sqrt(41 / 30) * Math.Pow(x, 3) + 1561 / 300 * Math.Sqrt(1561 / 300);


        //Func<double, double> dfunc2 = x => 1 / (2 * Math.Cbrt(x)) + 41 / 20 * x;



        Func<double, double> dfunc3 = x => Math.Sqrt(1 / 4.1) * 1 / Math.Sqrt(x) - Math.Sqrt(3 / 4.1) * 1 / Math.Cbrt(Math.Pow(x, 2));


        // работает! только для отрезка [2;2,2] (4)
        Func<double, double> func4 = x => 4 / 4.1 - 3 / 4.1 * 1 / Math.Cbrt(x) + 15.61 / (4.1 * x);
        Func<double, double> dfunc4 = x => (1 / Math.Cbrt(Math.Pow(Math.Abs(x), 4)) - 15.61 / Math.Pow(Math.Abs(x), 2)) / 4.1;

        // phi (1) ее используем для [-1,2;-1,4]
        Func<double, double> phi = x => (3 * Math.Cbrt(Math.Pow(x, 2.0)) + 4.1 * Math.Pow(x, 2) - 15.61) / 4;   // Функция для метода простых итераций
        Func<double, double> dphi = x => (1 / (2 * Math.Cbrt(x)) + 8.2 * x) / 4;   // Производная phi'

        Func<double, double> dfunc1 = x => (4 * Math.Sqrt(x) / Math.Sqrt(3)) - (3 * Math.Pow(41, 3 / 2) * x * Math.Abs(x)) / Math.Pow(30, 3 / 2);
        //Func<double, double> func1 = x =>

        //Func<double, double> dfunc5 = x => (4 * Math.Pow(x, 1 / 2)) / Math.Sqrt(3) - (3 * Math.Pow(41, 3 / 2) * x * Math.Abs(x)) / Math.Pow(30, 3 / 2);

        //Func<double, double> dfunc4 = x => -3.4689 * Math.Pow(x, -5.0 / 3.0) + 0.4444 * Math.Pow(x, -2.0 / 3.0) - 1.8222 * Math.Pow(x, 1.0 / 3.0);





        double p = -1.4;
        double calc_f = f(p);
        double calc_df = df(p);

        double calc_ddf = ddf(p);

        //Console.WriteLine($"Значение функции в точке {p}: {calc_f}");
        //Console.WriteLine($"Значение производной функции в точке {p}: {calc_df}");
        //Console.WriteLine($"Значение второй производной в точке {p}: {calc_ddf}");

        //Console.WriteLine("   x         dfunc4(x)");
        //Console.WriteLine("---------------------");

        double left = -1.4;
        double right = -1.2;
        double step = 0.01;
        for (double x = left; x <= right + step; x += step)
        {
            double dfunc4x = F(x);
            Console.WriteLine($"{x,6:F2}    {dfunc4x,10:F5}");
        }


        Console.WriteLine("   x         F(x)");
        Console.WriteLine("---------------------");

        for (double x = left; x <= right + 0.01; x += step)
        {
            double phix = phi(x);
            Console.WriteLine($"{x,6:F2}    {phix,10:F5}");
        }

        double a = -2, b = 3, x0 = 2.1;

        double[] epsilons = { 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8 };

        double i = a;
        double h = 0.2;


        // Вывод заголовка таблицы
        //Console.WriteLine("   x         f(x)");
        //Console.WriteLine("---------------------");

        // Выполняем табулирование
        //for (double x = a; x <= b+h; x += h)
        //{
         //   double fx = f(x);
         //   Console.WriteLine($"{x,6:F2}    {fx,10:F5}");
        //}

        foreach (var epsilon in epsilons)
        {
            //BisectionMethod(f, 2, 2.2, epsilon);

            //BisectionMethod(f, -1.4, -1.2, epsilon);
            //NewtonMethod(f, df, x0, epsilon);
            //SecantMethod(f, a, b, epsilon);
            //SimpleIterationMethod(phi, x0, epsilon);
        }

        Console.WriteLine("==========================================");
        foreach (var epsilon in epsilons)
        {
            //BisectionMethod(f, 2, 2.2, epsilon);

            //BisectionMethod(f, -1.4, -1.2, epsilon);
            //NewtonMethod(f, df, x0, epsilon);
            //SecantMethod(f, -1.4, -1.2, epsilon);
            //SimpleIterationMethod(phi, 2.1, epsilon);
        }



        foreach (var epsilon in epsilons)
        {
            // Заголовок для текущего значения epsilon
            Console.WriteLine($"Точность: {epsilon}");
            Console.WriteLine("--------------------------------------------------");
            Console.WriteLine($"| Метод              | Итерации | Приближённое значение |");
            Console.WriteLine("--------------------------------------------------");

            // Вызов методов с выводом итераций и приближённого корня

            // Метод бисекций
            double bisRoot = BisectionMethod(F, maksLeft, maksRight, epsilon);

            // Метод Ньютона
            double newtonRoot = NewtonMethod(F, dmaks, maksRight, epsilon);

            // Метод хорд (секущих)
            double secantRoot = SecantMethod(F, maksLeft, maksRight, epsilon);

            // Метод простых итераций
            SimpleIterationMethod(F, (maksLeft+maksRight)/2, epsilon);

            Console.WriteLine("--------------------------------------------------\n");
        }


        //string filePath = "results.csv";
        //using (StreamWriter writer = new StreamWriter(filePath, false, Encoding.UTF8))
        //{
        //    foreach (var epsilon in epsilons)
        //    {
        //        double bisRoot = BisectionMethod(f, -1.4, -1.2, epsilon, writer);
        //        double newtonRoot = NewtonMethod(f, df, x0, epsilon, writer);
        //        double secantRoot = SecantMethod(f, -1.4, -1.2, epsilon, writer);
        //    }
        //}

        //Console.WriteLine("Результаты сохранены в файл: " + filePath);

    }
    // Метод бисекций с записью результатов в CSV
    static double BisectionMethod(Func<double, double> f, double a, double b, double epsilon, StreamWriter writer)
    {
        double c = (a + b) / 2.0;
        int iterations = 0;

        while (Math.Abs(b - a) > epsilon)
        {
            if (f(c) == 0.0) break;
            if (f(a) * f(c) < 0)
                b = c;
            else
                a = c;

            c = (a + b) / 2.0;
            iterations++;
        }

        // Форматирование до 10 знаков после запятой
        writer.WriteLine($"{epsilon:F10},Бисекции,{iterations},{c:F10}");
        return c;
    }

    // Метод Ньютона с записью результатов в CSV
    static double NewtonMethod(Func<double, double> f, Func<double, double> df, double x0, double epsilon, StreamWriter writer)
    {
        double x = x0;
        int iterations = 0;
        while (Math.Abs(f(x)) > epsilon)
        {
            x = x - f(x) / df(x);
            iterations++;
        }

        // Форматирование до 10 знаков после запятой
        writer.WriteLine($"{epsilon:F10},Ньютон,{iterations},{x:F10}");
        return x;
    }

    // Метод хорд (секущих) с записью результатов в CSV
    static double SecantMethod(Func<double, double> f, double a, double b, double epsilon, StreamWriter writer)
    {
        double x0 = a, x1 = b;
        double x2;
        int iterations = 0;

        while (Math.Abs(x1 - x0) > epsilon)
        {
            x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
            x0 = x1;
            x1 = x2;
            iterations++;
        }

        // Форматирование до 10 знаков после запятой
        writer.WriteLine($"{epsilon:F10},Хорды (секущие),{iterations},{x1:F10}");
        return x1;
    }






    static double BisectionMethod(Func<double, double> f, double a, double b, double epsilon)
    {
        double c = (a + b) / 2.0;
        int iterations = 0;

        while (Math.Abs(b - a) > epsilon)
        {
            if (f(c) == 0.0) break;
            if (f(a) * f(c) < 0)
                b = c;
            else
                a = c;

            c = (a + b) / 2.0;
            iterations++;
        }

        //Console.WriteLine($"Метод бисекций: {iterations} итераций для точности {epsilon}");
        //Console.WriteLine($"Полученное значение: {c}");
        //Console.WriteLine("--------------------------------------------------");
        Console.WriteLine($"| Бисекции           | {iterations,8} | {c,22:F10} |");
        return c;
    }

    static double NewtonMethod(Func<double, double> f, Func<double, double> df, double x0, double epsilon)
    {
        double x = x0;
        int iterations = 0;
        while (Math.Abs(f(x)) > epsilon)
        {
            x = x - f(x) / df(x);
            iterations++;
        }
        //Console.WriteLine($"Приближенное значение корня: {x}");
        //Console.WriteLine($"Метод Ньютона: {iterations} итераций для точности {epsilon}");
        Console.WriteLine($"| Ньютон             | {iterations,8} | {x,22:F10} |");
        return x;
    }

    static double SecantMethod(Func<double, double> f, double a, double b, double epsilon)
    {
        double x0 = a, x1 = b;
        double x2;
        int iterations = 0;

        while (Math.Abs(x1 - x0) > epsilon)
        {
            x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
            x0 = x1;
            x1 = x2;


            iterations++;
        }
        //Console.WriteLine($"Приближенное значение корня: {x1}");
        //Console.WriteLine($"Метод хорд: {iterations} итераций для точности {epsilon}");
        Console.WriteLine($"| Хорды (секущие)    | {iterations,8} | {x1,22:F10} |");
        return x1;
    }

    static double SimpleIterationMethod(Func<double, double> phi, double x0, double epsilon)
    {
        // берем произвольное значение из отрезка например x0
        double x = x0;
        int iterations = 0;

        // проверяем если нашли корень с достаточной точностью
        while (Math.Abs(phi(x) - x) > epsilon)
        {
           // если не устраивает точность считаем значение функции phi
            x = phi(x);
            //Console.WriteLine($"получили: {x}");
            // и инкрементируем итерации
            iterations++;
        }
        //Console.WriteLine($"Приближенное значение корня: {x}");
        //Console.WriteLine($"Метод простых итераций: {iterations} итераций для точности {epsilon}");
        Console.WriteLine($"| Простые итер       | {iterations,8} | {x,22:F10} |");
        return x;
    }

}
