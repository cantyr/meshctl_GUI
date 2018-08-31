package meshgui;

import java.util.logging.Level;
import java.util.logging.Logger;

public class InitThreadRunnable implements Runnable {

    private Home home;

    public InitThreadRunnable(Home _home) {
        this.home = _home;
    }

    @Override
    public void run() {
        System.out.println( "Starting init thread!!!" );
        /*try {
            Thread.sleep(1000);
            synchronized( home ) {
                System.out.println( "Before notify!!!" );
                home.notify();
                home.init();
            }
        } catch (InterruptedException ex) {
            System.out.println( ex.toString() );
        }*/
        ThreadRunnable callbackRunnable = new ThreadRunnable(home);
        new Thread(callbackRunnable).start();
        home.init();
    }
}