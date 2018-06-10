

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!



public class UrlValidatorTest extends TestCase {
    
    // Valid schemes are described in RFC 3986  
    // Because a scheme is optional, the array starts with the empty string.
    String[] validScheme = {  "", 
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
    String[] validAuth = {};

    // Invalid Authorities are described in RFC 3986
    String[] invalidAuth = {};

    // Huff's contribution: programming-based testing   
    public void testIsValid()
    {

        String compStr;

        // Counters to track which subsets of the URL cause failures.
        // Pattern fails shouldn't be possible; using a composite string forces the URL to follow the pattern.
        int schemeFails = 0,
            authorityFails = 0,
            pathFails = 0,
            queryFails = 0,
            fragmentFails = 0;   

        for(){
        
            
        }
        
        // Call isValid with composite string representing valid URLs
        // If assertion fails, that iteration can lead to finding the exact fault
        // e.g. if path$test fails, then isValid is incorrectly disallowing the $ character in URLs.
        for(int i = 0; i < validScheme.length; i++){
        
            compStr = String.join(validScheme[i] +  +   );
            
        }
        
        // Call isValid with composite string representing invalid URLs  

    }
   


}
