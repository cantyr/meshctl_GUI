package meshgui;

public class ThreadRunnable implements Runnable {

    public static Home home;

    public ThreadRunnable(Home _home) {
        ThreadRunnable.home = _home;
    }

    public void run() {
        home.eventCallback();
    }
}