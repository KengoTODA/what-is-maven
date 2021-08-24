package jp.skypencil;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import org.junit.Test;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.MatcherAssert.assertThat;

public class MainTest {

    @Test
    public void testPrintMessage() {
        ByteArrayOutputStream binary = new ByteArrayOutputStream();
        PrintStream stream = new PrintStream(binary, true);
        PrintStream defaultStream = System.out;
        try {
            System.setOut(stream);
            new Main("message").execute();
            assertThat(binary.toString(), is("message" + System.getProperty("line.separator")));
        } finally {
            System.setOut(defaultStream);
        }
    }

    @Test(expected = IllegalArgumentException.class)
    public void testNullArgument() {
        new Main(null);
    }
}