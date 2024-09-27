interface IPrint
{
    void Print(string text);
}

abstract class Figure
{
    abstract public double Square();
}

class Rectangle : Figure, IPrint
{
    public int Lenght { get; set; }

    public int Width { get; set; }


    public void Print(string text)
    {
        Console.WriteLine(text);
    }

    public override double Square()
    {
        return Lenght * Width;
    }
    public override string ToString()
    {
        return ("Lenght of " + base.ToString() + ": " + Lenght.ToString()) + 
            ("\nWidth of " + base.ToString() + ": " + Width.ToString()) + 
            ("\nArea of " + base.ToString() + ": " + Square().ToString() + "\n");


    }
    public Rectangle(int lenght, int width)
    {
        this.Lenght = lenght;
        this.Width = width;
        Print(ToString());
    }
    public Rectangle(int lenght)
    {
        this.Lenght = lenght;
        Print(ToString());
    }

}
class Cube : Rectangle
{

    public override double Square()
    {
        return base.Lenght * base.Lenght;
    }
    public override string ToString()
    {
        return ("Lenght of " + this.GetType() + ": " + Lenght.ToString())
            + ("\nArea of " + this.GetType() + ": " + Square().ToString() + "\n");
    }
    public Cube(int lenght) : base(lenght) { }

}
class Circle : Figure, IPrint
{
    public int Radius { get; set; }

    public override double Square()
    {
        return Radius * Radius * Math.PI;
    }
    public void Print(string text)
    {
        Console.WriteLine(text);
    }
    public override string ToString()
    {
        return ("Radius of " + base.ToString() + ": " + Radius.ToString())
            + ("\nArea of " + base.ToString() + ": " + Square().ToString());
    }
    public Circle(int radius)
    {
        Radius = radius;
        Print(ToString());
    }
}

public class program
{
    static void Main()
    {
        const int a = 13;
        Rectangle rec = new Rectangle(a, a + 2);
        Cube cube = new Cube(a);
        Circle circle = new Circle(a);
    }
}

