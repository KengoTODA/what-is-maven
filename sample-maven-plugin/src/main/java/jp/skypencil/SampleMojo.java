package jp.skypencil;

import java.io.File;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugins.annotations.Execute;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;

/**
 * <p>Execute `mvn jp.skypencil:sample-maven-plugin:sample` to call this mojo.
 *
 * @author eller86
 * @version 0.0.1
 */
@Mojo(
        name = "sample",
        threadSafe = true
)
@Execute(
        goal = "sample",
        phase = LifecyclePhase.COMPILE
)
public class SampleMojo extends AbstractMojo {
    @Parameter(
            property = "project.build.directory",
            required = true
    )
    private File outputDirectory;

    @Override
    public void execute() throws MojoExecutionException {
        getLog().info("sample plugin start!");
        getLog().debug("project.build.directory is " + outputDirectory.getAbsolutePath());
    }
}
