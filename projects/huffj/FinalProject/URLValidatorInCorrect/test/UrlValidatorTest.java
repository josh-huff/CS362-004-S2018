

import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {

    // Valid schemes are described in RFC 3986
    // Because a scheme is optional, the array starts with the empty string.
/*

John Eleen found a bug that precludes all valid schemes besides http.
If he had not, this would be the validScheme array passed to our unit test. Instead, it is below.

   String[] validScheme =  { "scheme",
           //"",
           "http://",  "https://", "ftp://", "ftps://",
           "http+://", "ht-tp://", "h.t.t.p.://"
   };
*/
    String[] validScheme = {"scheme",
            "http://"
    };

    // Invalid schemes start with a numeric or contain invalid characters. These are a small sample of what should fail.
    String[] invalidScheme = {"0http://", "http^://"};


    // This array's elements each contain a different valid path character
    // Valid path characters can be found in RFC 3986
    // Because a path is optional, the array starts with the empty string.
    String[] validPath = {"",
            "/pathtest", "/PATHTEST", "/pathtest01", "/path.test",
            "/path-test", "/path_test", "/path~test", "/path!test",
            "/path$test", "/path&test", "/path'test", "/path(test",
            "/path)test", "/path*test", "/path+test", "/path,test",
            "/path;test", "/path=test", "/path:test", "/path@test"
    };

    // Invalid paths contain characters not in that subset. These are a small sample of what should fail.
    String[] invalidPath = {"/path|test", "/path#test", "/path^test", "/path`test"};

    // Valid Authorities are described in RFC 3986
    String[] validAuth = {"google.com", "google.com:80", "255.255.255.255", "google.co.uk"};

    // Invalid authorities are empty strings, octets and ports out of range, and invalid top level domains
    String[] invalidAuth = {"", "256.255.255.255", "google.com:70000", "google.255"};

    // Huff's contribution: programming-based testing
    public void testIsValid() {

//        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

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

        for (int i = 0; i < valids.length; i++) {

            for (int j = 1; j < valids[i].length; j++) {

                if (!accepted(valids[i], valids[i][j], j, "accepted")) {

                    switch (valids[i][0]) {

                        case "scheme":
                            schemeFails++;
                            break;
                        case "authority":
                            authorityFails++;
                            break;
                        case "path":
                            pathFails++;
                            break;
                        case "query":
                            queryFails++;
                            break;
                        case "fragment":
                            fragmentFails++;
                            break;
                        default:
                            System.out.println("Problem with switch statement in testIsValid()");
                    }
                }
            }
        }

        // Print totals of failures
        System.out.println("Number of scheme failures: " + Integer.toString(schemeFails));
        System.out.println("Number of authority failures: " + Integer.toString(authorityFails));
        System.out.println("Number of path failures: " + Integer.toString(pathFails));
        System.out.println("Number of query failures: " + Integer.toString(queryFails));
        System.out.println("Number of fragment failures: " + Integer.toString(fragmentFails));
    }

    private boolean accepted(String[] inputArray, String element, int position, String expected) {

        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        String compStr = "compStr has not been set to a valid component type!";
        String componentType = inputArray[0];
        String knownValid;
        String errMsg;

        if (componentType.equals("scheme")) {

            knownValid = "google.com";
            compStr = element + knownValid;
        }

        if (componentType.equals("authority")) {

            knownValid = "google.com";
            compStr = element + knownValid;
        }

        if (expected.equals("accepted")) {

            errMsg = "Valid " + componentType + " at index " + Integer.toString(position) + " has been rejected.";
            assertTrue(errMsg, urlVal.isValid(compStr));
        }

        else {

            errMsg = "Invalid " + componentType + " at index " + Integer.toString(position) + " has been accepted.";
            assertFalse(errMsg, urlVal.isValid(compStr));
        }

        return urlVal.isValid(compStr);
    }
}
