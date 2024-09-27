public class Triangle {
    // Координаты вершин треугольника
    protected double x1, y1;
    protected double x2, y2;
    protected double x3, y3;

    // Конструктор
    public Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
        this.x3 = x3;
        this.y3 = y3;
    }

    // Метод проверки существования треугольника
    public boolean isValid() {
        double a = distance(x1, y1, x2, y2);
        double b = distance(x2, y2, x3, y3);
        double c = distance(x3, y3, x1, y1);
        return a + b > c && b + c > a && c + a > b;
    }

    // Метод вычисления расстояния между двумя точками
    protected double distance(double x1, double y1, double x2, double y2) {
        return Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
    }

    // Метод вычисления периметра
    public double perimeter() {
        double a = distance(x1, y1, x2, y2);
        double b = distance(x2, y2, x3, y3);
        double c = distance(x3, y3, x1, y1);
        return a + b + c;
    }

    // Метод вычисления площади
    public double area() {
        double a = distance(x1, y1, x2, y2);
        double b = distance(x2, y2, x3, y3);
        double c = distance(x3, y3, x1, y1);
        double s = perimeter() / 2;
        return Math.sqrt(s * (s - a) * (s - b) * (s - c));
    }

    // Метод вычисления углов
    public double[] angles() {
        double a = distance(x1, y1, x2, y2);
        double b = distance(x2, y2, x3, y3);
        double c = distance(x3, y3, x1, y1);
        double angleA = Math.toDegrees(Math.acos((b * b + c * c - a * a) / (2 * b * c)));
        double angleB = Math.toDegrees(Math.acos((a * a + c * c - b * b) / (2 * a * c)));
        double angleC = 180 - angleA - angleB;
        return new double[]{angleA, angleB, angleC};
    }

    // Метод вывода информации о треугольнике
    public void printInfo() {
        System.out.println("Треугольник:");
        System.out.println("Стороны: " + distance(x1, y1, x2, y2) + ", " + distance(x2, y2, x3, y3) + ", " + distance(x3, y3, x1, y1));
        double[] angles = angles();
        System.out.println("Углы: " + angles[0] + ", " + angles[1] + ", " + angles[2]);
        System.out.println("Периметр: " + perimeter());
        System.out.println("Площадь: " + area());
    }
}