import java.util.stream.IntStream;

public class ParallelTrapezoidalIntegrationWithStreams {
    public static void main(String[] args) {
        // Пределы интегрирования
        double a = 0; // Начало интервала
        double b = 1; // Конец интервала
        int n = 1000; // Число разбиений

        // Функция интегрирования
        Function<Double, Double> function = x -> Math.pow(x, 2); // f(x) = x^2

        // Параллельное вычисление интеграла
        double integral = parallelTrapezoidalIntegration(a, b, n, function);

        //System.out.println(Runtime.getRuntime().availableProcessors());

        System.out.println("Рассчитанное значение интеграла: " + integral);
    }

    public static double parallelTrapezoidalIntegration(double a, double b, int n, Function<Double, Double> function) {
        double h = (b - a) / n; // Шаг

        // Вычисление основной суммы параллельно
        double sum = IntStream.range(1, n) // Индексы от 1 до n-1
                              .parallel() // Параллельный поток
                              .mapToDouble(i -> function.apply(a + i * h)) // Вычисление f(x_i)
                              .sum();

        // Добавляем крайние точки (f(a) и f(b))
        sum += (function.apply(a) + function.apply(b)) / 2;

        // Умножаем на шаг
        return h * sum;
    }

    /**
     * Функциональный интерфейс для передачи функции.
     */
    @FunctionalInterface
    public interface Function<T, R> {
        R apply(T t);
    }
}
