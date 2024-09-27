import java.util.ArrayList;
import java.util.List;

public class Comp {
    private String serial;
    private String name;
    private List<Part> parts;

    public Comp(String name, String serial) {
        this.name = name;
        this.serial = serial;
        this.parts = new ArrayList<>();
    }

    public void AddPart(Part part) {
        parts.add(part);
    }

    public void getInfo() {
        System.out.printf("Computer: %s, Serial: %s\n", this.name, this.serial);
        for (int i = 0; i < parts.size(); i++) {
            System.out.printf("%d: ", i+1);
            parts.get(i).getInfo();
        }
    }

    public void ReplacePart(Part part, int i)
    {
        if (i >= 0 && i < parts.size()) {
            parts.set(i, part);
        } else {
            System.out.println("Invalid index");
        }
    }

}


