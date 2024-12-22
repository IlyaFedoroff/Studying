import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class ParallelTrapezoidalIntegration {
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        // Пределы интегрирования
        double a = 0; // Начало интервала
        double b = 1; // Конец интервала
        int n = 1000; // Число разбиений

        // Функция интегрирования
        Function<Double, Double> function = x -> Math.pow(x, 2); // f(x) = x^2

        // Параллельное вычисление интеграла
        double integral = parallelTrapezoidalIntegration(a, b, n, function);
        System.out.println("Рассчитанное значение интеграла: " + integral);
    }

    /**
     * Метод для параллельного вычисления интеграла по формуле трапеций.
     */
    public static double parallelTrapezoidalIntegration(double a, double b, int n, Function<Double, Double> function)
            throws InterruptedException, ExecutionException {
        ExecutorService executor = Executors.newFixedThreadPool(4); // Пул потоков
        int numThreads = 4; // Число потоков
        double h = (b - a) / n; // Шаг

        // Список задач для выполнения
        List<Future<Double>> futures = new ArrayList<>();
        int chunkSize = (int) Math.ceil((double) n / numThreads);

        for (int i = 0; i < numThreads; i++) {
            final int start = i * chunkSize;
            final int end = Math.min((i + 1) * chunkSize, n);

            // Добавляем задачу для вычисления частичной суммы
            futures.add(executor.submit(() -> calculatePartialSum(a, h, start, end, function)));
        }
        // Поток 1: считает трапеции от точки a + 0 * h до a + 250 * h.
        // Поток 2: считает трапеции от точки a + 250 * h до a + 500 * h.
        // Поток 3: считает трапеции от точки a + 500 * h до a + 750 * h.
        // Поток 4: считает трапеции от точки a + 750 * h до a + 1000 * h.

        // Ожидаем завершения задач и складываем результаты
        double sum = 0.0;
        for (Future<Double> future : futures) {
            sum += future.get();
        }

        executor.shutdown();

        // Учитываем крайние точки (f(a) и f(b))
        sum += (function.apply(a) + function.apply(b)) / 2;

        // Умножаем на шаг для получения окончательного результата
        return h * sum;
    }

    /**
     * Метод для вычисления частичной суммы трапеций на заданном интервале.
     */
    private static double calculatePartialSum(double a, double h, int start, int end, Function<Double, Double> function) {
        double sum = 0.0;
        for (int i = start; i < end; i++) {
            double x = a + i * h;
            sum += function.apply(x);
        }
        return sum;
    }

    /**
     * Функциональный интерфейс для передачи функции.
     */
    @FunctionalInterface
    public interface Function<T, R> {
        R apply(T t);
    }
}
