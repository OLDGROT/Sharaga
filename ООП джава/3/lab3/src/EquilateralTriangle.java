public class EquilateralTriangle extends Triangle {

    // Конструктор
    public EquilateralTriangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        super(x1, y1, x2, y2, x3, y3);
    }

    // Метод проверки равностороннего треугольника
    public boolean isEquilateral() {
        double a = distance(super.x1, super.y1, super.x2, super.y2);
        double b = distance(super.x2, super.y2, super.x3, super.y3);
        double c = distance(super.x3, super.y3, super.x1, super.y1);
        return a == b && b == c;
    }

    @Override
    public void printInfo() {
        super.printInfo();
        if (isEquilateral()) {
            System.out.println("Этот треугольник равносторонний.");
        } else {
            System.out.println("Этот треугольник не является равносторонним.");
        }
    }
}