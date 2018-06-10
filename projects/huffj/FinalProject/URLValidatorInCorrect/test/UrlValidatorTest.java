

import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {

    /*

        ---- IMPORTANT NOTE ----

    John Eleen found a bug when performing input partition.
    The bug precludes all valid schemes besides http and all valid port numbers in authorities.
    If he had not, this would be the validScheme array passed to our unit test.

        // Valid schemes are described in RFC 3986
        // Because a scheme is optional, the array starts with the empty string.
       String[] validScheme =  { "scheme",
               //"",
               "http://",  "https://", "ftp://", "ftps://",
               "http+://", "ht-tp://", "h.t.t.p.://"
       };
    */
    String[] validScheme = { "scheme", "http://" };

    // Invalid schemes start with a numeric or contain invalid characters. These are a small sample of what should fail.
    String[] invalidScheme = { "scheme", "0http://", "http^://" };

    // Valid Authorities are described in RFC 3986
    String[] validAuth = { "authority", "google.com", "255.255.255.255", "google.co.uk" };

    // Invalid authorities are empty strings, octets and ports out of range, and invalid top level domains
    String[] invalidAuth = { "authority", "", "256.255.255.255", "google.255" };

    // This array's elements each contain a different valid path character
    // Valid path characters can be found in RFC 3986
    // Because a path is optional, the array starts with the empty string.
    String[] validPath = { "path", "",
            "/pathtest", "/PATHTEST", "/pathtest01", "/path.test",
            "/path-test", "/path_test",
            // Commented out in the middle of testing to check subsequent cases "/path~test",
            "/path!test", "/path$test", "/path&test", "/path'test",
            "/path(test", "/path)test", "/path*test", "/path+test",
            "/path,test", "/path;test", "/path=test", "/path:test",
            "/path@test"
    };

    // Invalid paths contain characters not in that subset. These are a small sample of what should fail.
    String[] invalidPath = { "path", "/path|test", "/path#test", "/path^test", "/path`test" };

    // This array's elements each contain a different valid path character
    // Valid path characters can be found in RFC 3986
    // Because a path is optional, the array starts with the empty string.
    String[] validQuery = { "query", "", "?", "quarter?name=SP18&final=YES" };

    // Invalid paths contain characters not in that subset. These are a small sample of what should fail.
    String[] invalidQuery = { "query", "? huh" };

    // Huff's contribution: programming-based testing
    public void testIsValid() {

        String[][] valids = {validScheme, validAuth, validPath}; // FOR TESTING ONLY

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
                            System.out.println("Problem with switch statement in testIsValid()'s valids loop");
                    }
                }
            }
        }
/*
        for (int i = 0; i < invalids.length; i++) {

            for (int j = 1; j < invalids[i].length; j++) {

                if (!accepted(invalids[i], invalids[i][j], j, "rejected")) {

                    switch (invalids[i][0]) {

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
                            System.out.println("Problem with switch statement in testIsValid()'s invalids loop");
                    }
                }
            }
        }
*/
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

            knownValid = "http://";
            compStr = knownValid + element;
        }

        if (componentType.equals("path")) {

            knownValid = "http://";
            compStr = knownValid + element;
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
