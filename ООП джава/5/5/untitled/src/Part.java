public class Part {
    private String name;
    public String price;
    public String warranty;

    public Part(String name, String price, String warranty)
    {
        this.name = name;
        this.price = price;
        this.warranty = warranty;
    }

    public void getInfo()
    {
        System.out.printf("Part: %s, Price: %s, Warranty: %s%n", this.name, this.price, this.warranty);
    }
}
