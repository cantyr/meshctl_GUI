package meshgui;

import java.util.logging.Level;
import java.util.logging.Logger;

public class ThreadRunnable implements Runnable {

    private Home home;

    public ThreadRunnable(Home _home) {
        this.home = _home;
    }

    public void run() {
        System.out.println( "Starting callback thread!!!" );
        /*synchronized(home) {
            try {
                System.out.println( "WAITING . . . " );
                home.wait();
            } catch (InterruptedException ex) {
                System.out.println( ex.toString() );
            }
            System.out.println( "Starting callback thread!!!" );
            home.eventCallback();
        }*/
        home.eventCallback();
    }
}