import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        int N = 3; // количество обычных треугольников
        int M = 3; // количество равносторонних треугольников

        List<Triangle> triangles = new ArrayList<>();
        List<EquilateralTriangle> equilateralTriangles = new ArrayList<>();

        // Создание N обычных треугольников с целочисленными сторонами
        triangles.add(new Triangle(0, 0, 3, 0, 0, 4)); // Стороны: 3, 4, 5
        triangles.add(new Triangle(0, 0, 4, 0, 0, 3)); // Стороны: 4, 3, 5
        triangles.add(new Triangle(0, 0, 5, 0, 0, 12)); // Стороны: 5, 12, 13

        // Создание M равносторонних треугольников с целочисленными сторонами
        equilateralTriangles.add(new EquilateralTriangle(0, 0, 3, 0, 1.5, Math.sqrt(6.75))); // Сторона: 3
        equilateralTriangles.add(new EquilateralTriangle(0, 0, 6, 0, 3, Math.sqrt(27))); // Сторона: 6
        equilateralTriangles.add(new EquilateralTriangle(0, 0, 9, 0, 4.5, Math.sqrt(60.75))); // Сторона: 9

        // Вывод информации о треугольниках
        System.out.println("Обычные треугольники:");
        for (int i = 0; i < triangles.size(); i++) {
            System.out.println("Треугольник " + (i + 1) + ":");
            if (triangles.get(i).isValid()) {
                triangles.get(i).printInfo();
            } else {
                System.out.println("Этот треугольник не существует.");
            }
            System.out.println();
        }

        System.out.println("Равносторонние треугольники:");
        for (int i = 0; i < equilateralTriangles.size(); i++) {
            System.out.println("Равносторонний треугольник " + (i + 1) + ":");
            if (equilateralTriangles.get(i).isValid()) {
                equilateralTriangles.get(i).printInfo();
            } else {
                System.out.println("Этот треугольник не существует.");
            }
            System.out.println();
        }

        // Поиск и вывод номеров одинаковых треугольников
        System.out.println("Одинаковые треугольники:");
        for (int i = 0; i < triangles.size(); i++) {
            for (int j = i + 1; j < triangles.size(); j++) {
                if (areTrianglesEqual(triangles.get(i), triangles.get(j))) {
                    System.out.println("Треугольники " + (i + 1) + " и " + (j + 1) + " одинаковые.");
                }
            }
        }

        // Поиск равностороннего треугольника с наименьшей медианой
        EquilateralTriangle minMedianTriangle = null;
        double minMedian = Double.MAX_VALUE;
        for (EquilateralTriangle triangle : equilateralTriangles) {
            double median = calculateMedian(triangle);
            if (median < minMedian) {
                minMedian = median;
                minMedianTriangle = triangle;
            }
        }

        System.out.println("Равносторонний треугольник с наименьшей медианой:");
        if (minMedianTriangle != null) {
            minMedianTriangle.printInfo();
            System.out.println("Наименьшая медиана: " + minMedian);
        } else {
            System.out.println("Нет действительных равносторонних треугольников.");
        }
    }

    // Метод для проверки равенства двух треугольников по длине сторон
    private static boolean areTrianglesEqual(Triangle t1, Triangle t2) {
        double[] sides1 = getSortedSides(t1);
        double[] sides2 = getSortedSides(t2);
        for (int i = 0; i < 3; i++) {
            // Фикс сравнения числа с плавающей точкой
            if (Math.abs(sides1[i] - sides2[i]) > 1e-6) {
                return false;
            }
        }
        return true;
    }

    // Метод для получения отсортированных длин сторон треугольника
    private static double[] getSortedSides(Triangle t) {
        double a = t.distance(t.x1, t.y1, t.x2, t.y2);
        double b = t.distance(t.x2, t.y2, t.x3, t.y3);
        double c = t.distance(t.x3, t.y3, t.x1, t.y1);
        double[] sides = {a, b, c};
        java.util.Arrays.sort(sides);
        return sides;
    }

    // Метод для вычисления медианы равностороннего треугольника
    private static double calculateMedian(EquilateralTriangle t) {
        double side = t.distance(t.x1, t.y1, t.x2, t.y2);
        return Math.sqrt(3) / 2 * side;
    }
}