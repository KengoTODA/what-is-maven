package jp.skypencil;

import java.io.File;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;

/**
 * Execute `mvn jp.skypencil:sample-maven-plugin:sample` to call this mojo.
 */
@Mojo(
        name = "sample",
        threadSafe = true,
        defaultPhase = LifecyclePhase.COMPILE
)
public class SampleMojo extends AbstractMojo {
    @Parameter(
            property = "project.build.directory",
            required = true
    )
    private File outputDirectory;

    @Override
    public void execute() throws MojoExecutionException {
        if (outputDirectory == null) {
            throw new MojoExecutionException("outputDirectory is required");
        }

        getLog().info("sample plugin start!");
        getLog().debug("outputDirectory is " + outputDirectory.getAbsolutePath());
    }
}
