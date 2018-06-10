

import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {
    
    // Valid schemes are described in RFC 3986  
    // Because a scheme is optional, the array starts with the empty string.
    String[] validScheme =  { "scheme",
                              "",
                              "http://",  "https://", "ftp://", "ftps://",
                              "http+://", "ht-tp://", "h.t.t.p.://"
                            };

    // Invalid schemes start with a numeric or contain invalid characters. These are a small sample of what should fail.
    String[] invalidScheme = { "0http://", "http^://"};
      
 
    // This array's elements each contain a different valid path character
    // Valid path characters can be found in RFC 3986
    // Because a path is optional, the array starts with the empty string. 
    String[] validPath = {  "", 
                            "/pathtest",  "/PATHTEST", "/pathtest01", "/path.test", 
                            "/path-test", "/path_test", "/path~test", "/path!test", 
                            "/path$test", "/path&test", "/path'test", "/path(test",
                            "/path)test", "/path*test", "/path+test", "/path,test", 
                            "/path;test", "/path=test", "/path:test", "/path@test"
                         };

    // Invalid paths contain characters not in that subset. These are a small sample of what should fail.
    String[] invalidPath = { "/path|test", "/path#test", "/path^test", "/path`test" };
    
    // Valid Authorities are described in RFC 3986
    String[] validAuth = {"google.com", "google.com:80", "255.255.255.255", "google.co.uk"};

    // Invalid authorities are empty strings, octets and ports out of range, and invalid top level domains
    String[] invalidAuth = {"", "256.255.255.255", "google.com:70000", "google.255"};

    // Huff's contribution: programming-based testing   
    public void testIsValid(){

        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        String compStr;
//        String[][] valids = {validScheme, validPath, validAuth};
        String[][] valids = {validScheme}; // FOR TESTING ONLY

        // Counters to track which subsets of the URL cause failures.
        // Pattern fails shouldn't be possible; using a composite string forces the URL to follow the pattern.
        int schemeFails = 0,
            authorityFails = 0,
            pathFails = 0,
            queryFails = 0,
            fragmentFails = 0;

        for(int i = 0; i < valids.length ; i++){

            for(int j = 1; j <= valids[i].length; j++) {

                if(!accepted(urlVal, valids[i], valids[i][j], j,"accepted")){

                    switch(valids[i][0]){

                        case "scheme":
                            schemeFails++;
                            break;
                        case "authority":
                            authorityFails++;
                        case "path":
                            pathFails++;
                        case "query":
                            queryFails++;
                        case "fragment":
                            fragmentFails++;
                        default:
                            System.out.println("Problem with switch statement in testIsValid()");
                    }
                }
            }
        }

/*
        // Call isValid with composite string representing known valid schemes with known valid bodies
        // If assertion fails, that iteration can lead to finding the exact fault
        // e.g. if http+:// fails, then isValid is incorrectly disallowing the + character in schemes.
        for(int i = 1; i <= validScheme.length; i++){
        
            compStr = validScheme[i] + "google.com";
            errMsg = "Valid scheme at index " + Integer.toString(i) + " has being rejected.";
            assertTrue(errMsg, urlVal.isValid(compStr));
            if(! urlVal.isValid(compStr)){schemeFails++;}
        }

        // Call isValid with composite string representing known invalid schemes and known valid bodies.
        // If assertion fails, that iteration can lead to finding the exact fault
        // e.g. if 0http:// succeeds, then isValid is incorrectly permitting a numeric character in front of a scheme.
        for(int i = 1; i <= invalidScheme.length; i++){

            compStr = invalidScheme[i] + "google.com";
            errMsg = "Invalid scheme at index " + Integer.toString(i) + " has being accepted.";
            assertTrue(errMsg, urlVal.isValid(compStr));
            if(! urlVal.isValid(compStr)){schemeFails++;}
        }
*/
        // Print totals of failures


    }

    public boolean accepted(UrlValidator urlVal, String[] inputArray, String element, int position, String expected){

        String compStr;
        String componentType = inputArray[0];
        String knownValid;
        String errMsg;

        if(expected == "accepted"){

            errMsg = "Valid " + componentType + " at index " Integer.toString(position) + " has been rejected."
        }
        else{

            errMsg = "Invalid " + componentType + " at index " + Integer.toString(position) + " has been accepted."
        }

        if(componentType == "scheme") {

            knownValid = "google.com";
            compStr = element + knownValid;
        }

        assertTrue(errMsg, urlVal.isValid(compStr));
        return urlVal.isValid(compStr));

        /*
        if(componentType == "authority") {

        }

        if(componentType == "scheme") {

        }
*/


    }
}
