package jp.skypencil;

public class Main {
    public static void main(String args[]) {
        new Main("Hello").execute();
    }

    private final String message;

    public Main(String message) {
        if (message == null) {
            throw new IllegalArgumentException();
        }
        this.message = message;
    }

    void execute() {
        System.out.println(message);
    }
}