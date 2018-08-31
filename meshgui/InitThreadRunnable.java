package meshgui;

import java.util.logging.Level;
import java.util.logging.Logger;

public class InitThreadRunnable implements Runnable {

    private Home home;

    public InitThreadRunnable(Home _home) {
        this.home = _home;
    }

    public synchronized void run() {
        System.out.println( "Starting init thread!!!" );
        /*try {
            Thread.sleep(1000);
            synchronized( home ) {
                System.out.println( "Before notify!!!" );
                home.notifyAll();
                System.out.println( "After notify!!!" );
                home.init();
            }
        } catch (InterruptedException ex) {
            Logger.getLogger(InitThreadRunnable.class.getName()).log(Level.SEVERE, null, ex);
        }*/
        home.init();
    }
}