package app;

import javafx.application.Application;

/**
 * The class that launches javafx application.
 *
 */
public final class App {

    private App() {
        // the constructor will never be called directly.
    }

    /**
     * Main method.
     * 
     * @param args
     */
    public static void main(final String... args) {
        Application.launch(MetalShot.class, args);
    }
}
