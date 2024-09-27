import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.println("Building PC...");
        System.out.println("Enter label and serial number: ");
        String label = in.next();
        String serial = in.next();

        System.out.println("Success! Result: ");

        Comp pc = new Comp(label,serial);

        pc.getInfo();

        System.out.println("Adding some parts...");

        for (int i = 0; i < 3; i++)
        {
            System.out.println("Enter a Part's name, price and warranty period...");
            String name = in.next();
            String price = in.next();
            String warranty = in.next();

            Part part = new Part(name,price,warranty);

            pc.AddPart(part);
        }

        System.out.println("Success! Result: ");
        pc.getInfo();

        System.out.println("Now time to replace some parts. Which part you want to replace?");
        int index = in.nextInt();
        System.out.println("Enter new Part's name, price and warranty period...");
        String name = in.next();
        String price = in.next();
        String warranty = in.next();

        Part newpart = new Part(name,price,warranty);

        pc.ReplacePart(newpart,index-1);

        System.out.println("Success! Result: ");

        pc.getInfo();
    }
}
