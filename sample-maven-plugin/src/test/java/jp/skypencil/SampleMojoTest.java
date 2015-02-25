package jp.skypencil;

import static org.junit.Assert.assertNotNull;

import java.io.File;

import org.apache.maven.plugin.Mojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.logging.Log;
import org.apache.maven.plugin.testing.MojoRule;
import org.apache.maven.plugin.testing.resources.TestResources;
import org.codehaus.plexus.component.repository.exception.ComponentLookupException;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.mockito.Mockito;

public class SampleMojoTest {
    private Log log;

    @Rule
    public MojoRule mojo = new MojoRule();

    @Rule
    public TestResources resources = new TestResources();

    @Before
    public void createLog() {
        log = Mockito.mock(Log.class);
    }

    @Test
    public void testMojoHasHelpGoal() throws Exception {
        // Use src/test/projects/no-output-dir/pom.xml to lookup Mojo
        File baseDir = resources.getBasedir("no-output-dir");
        File pom = new File(baseDir, "pom.xml");

        Mojo samplePlugin = mojo.lookupMojo("help", pom);
        assertNotNull(samplePlugin);
        samplePlugin.setLog(log);
        samplePlugin.execute();
    }

    @Test(expected = ComponentLookupException.class)
    public void testMojoHasNoFooBarGoal() throws Exception {
        File baseDir = resources.getBasedir("no-output-dir");
        File pom = new File(baseDir, "pom.xml");

        mojo.lookupMojo("foo-bar", pom);
    }

    @Test(expected = MojoExecutionException.class)
    public void testSampleGoalRequiresOutputDir() throws Exception {
        File baseDir = resources.getBasedir("no-output-dir");
        File pom = new File(baseDir, "pom.xml");

        Mojo samplePlugin = mojo.lookupMojo("sample", pom);
        samplePlugin.execute();
    }

    @Test
    public void testSampleGoalPrintsOutputDirectory() throws Exception {
        File baseDir = resources.getBasedir("simple");
        File pom = new File(baseDir, "pom.xml");

        Mojo samplePlugin = mojo.lookupMojo("sample", pom);
        samplePlugin.setLog(log);
        samplePlugin.execute();
        Mockito.verify(log).debug("outputDirectory is /tmp/target");
    }
}
