
namespace lab2
{
    public interface IPrint
    {
        public void Print() { }
    }

    public abstract class Figure
    {
        public virtual void GetArea() { }
    }

    public class Rectangle : Figure, IPrint
    {
        double area;
        public double Width { get; set; }
        public double Height { get; set; }
        public double Area { get; }

        public override void GetArea() { area = Width * Height; }

        public override string ToString()
        {
            return ($"Rectangle area is: {Width * Height}, Width is {Width} and Height is {Height}");
        }
        public void Print() { Console.WriteLine(ToString()); }

        public Rectangle(double width, double height)
        {
            Width = width; Height = height;
        }
    }

    public class Square : Rectangle, IPrint
    {
        double area, lenght;
        public Square(double lenght) : base(lenght, lenght) { }
        public override void GetArea() { area = lenght * lenght; }
        public override string ToString()
        {
            return ($"Square area is: {Width * Width}, Lenght of a side is {Width}");
        }
    }

    public class Circle : Figure, IPrint
    {
        double area;

        public double Radius { get; set; }
        public override void GetArea() { area = Radius * Radius; }
        public override string ToString()
        {
            return ($"Circle area is: {Radius * Radius * 3.1415}, Radius is {Radius}");
        }
        public void Print() { Console.WriteLine(ToString()); }
        public Circle(double radius)
        {
            Radius = radius;
        }
    }

    public class Program
    {
        public static void Main()
        {
            Console.WriteLine("2th Lab...");

            Rectangle rec = new Rectangle(10, 20);
            rec.Print();
            Square square = new Square(15);
            square.Print();
            Circle circle = new Circle(30);
            circle.Print();
        }
    }
}