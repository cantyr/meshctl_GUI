package meshgui;

public class Device {

	String uuid;
        String name;

	public Device( String _uuid, String _name ) {
            this.uuid = _uuid;
            this.name = _name;
	}
        
        public void setName( String _name ) {
            this.name = _name;
        }
        
        public String getName() {
            return name;
        }
        
        public String getUUID() {
            return uuid;
        }
        
        public String getDetails() {
            return name + " : " + uuid;
        }
}