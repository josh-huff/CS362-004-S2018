

import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {
    
    // Valid schemes are described in RFC 3986  
    // Because a scheme is optional, the array starts with the empty string.
    String[] validScheme =  { "",
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
    String[] validAuth = {"google.com", "255.255.255.255", "google.co.uk"};

    // Invalid authorities are empty strings, octets out of byte range, and invalid top level domains
    String[] invalidAuth = {"", "256.255.255.255", "google.255"};

    // Huff's contribution: programming-based testing   
    public void testIsValid()
    {

        UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        String compStr;

        // Counters to track which subsets of the URL cause failures.
        // Pattern fails shouldn't be possible; using a composite string forces the URL to follow the pattern.
        int schemeFails = 0,
            authorityFails = 0,
            pathFails = 0,
            queryFails = 0,
            fragmentFails = 0;   
/*
        for(){
        
            
        }
*/
        // Call isValid with composite string representing valid URLs
        // If assertion fails, that iteration can lead to finding the exact fault
        // e.g. if path$test fails, then isValid is incorrectly disallowing the $ character in URLs.
        for(int i = 0; i < validScheme.length; i++){
        
            compStr = String.join(validScheme[i] + "google.com" +   );
            
        }
        
        // Call isValid with composite string representing invalid URLs  

    }
   


}
