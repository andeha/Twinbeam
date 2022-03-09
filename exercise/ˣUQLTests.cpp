/*  UQLTests.cpp ╎ Helixstore/Turbine/UQL Unit Tests. */

#include <Additions/History.h>
/* #include <Additions/Security.h> */

/*
 
 Test case exercising the following: 
 
 1) Non-chronological commits that are sorted and evaluated
 
 2) Subgraphs, entities and keys created on-demand and awarded with an
  entry in a log
 
 3) Structural- and temporal amendments illustrated in two views
 
 3.5) Gaussian algebra
 
 4) A global 𝑐𝑢𝑟𝑟𝑒𝑛𝑡 𝑙𝑜𝑐𝑎𝑡𝑖𝑜𝑛 handy in multithreaded apps and concurrent
  database updates
 
 Todo: Consider limiting `currentGraphPath` to enclosing timestamp (i.e
  current transaction) only.
 
 */

const char32_t * READONLY initial = R"(
    2012-01-01 12:00:00 !
        VAR passive = Sum([Sg_1]⸺[Sg_2]>⸺<v0>{A1920}, LastMonth) + 1.00
        VAR amount = Normal(102.00, 10.00), passive
        [Sg_1]⸺[Sg_2]>⸺<v1>{A1920} ↑ amount
        ⸺<<2⸺<v2>{A1920} ↑ Swap(amount) // Permutes a double-stranded value
    2012-01-01 13:00:00 ! [Sg_1]⸺[Sg_2]>⸺<v3>{A1920} ↑ 32.32, 200.32 ⬷ '9bb5ce27-2f74-49c6-bcc3-e1e59c6a83e5'
    2012-01-01 13:00:00 ! [Sg_1]⸺[Sg_2]>⸺<v3>{A1920} ↓ 32.32, 200.32 // Equivalent to ↑ -32.32, -200.32
    // prompt> PRINT SampleAfter('9bb5ce27-2f74-49c6-bcc3-e1e59c6a83e5')
    // prompt> PRINT SampleBefore('9bb5ce27-2f74-49c6-bcc3-e1e59c6a83e5')
    // prompt> PRINT SampleBefore(2012-01-01 13:00:00)
    // prompt> PEEK
    // prompt> COMMIT NOW
)";

/*
 
 Monte-Carlo Section 
 
 Note that we choose to use a single quoted string instead of an identifier.
 
 We escape the ' with a \' and \ with \\. Consider regular expressions.
 
 */

const char32_t * READONLY update = R"(
    2012-01-01 12:00:00 @ '9bb5ce27-2f74-49c6-bcc3-e1e59c6a83e5' = 33.32 + 1.00, 200.33
)";

/*
 
 Querying: Since we have a query prefix, we know that: 1) The internal
 state of the complex is unaltered. 2) Querying requires interest in
 just one view.
 
 */

const char32_t * READONLY query₁ = R"(
    2012-01-01 12:00:00 ? 0.3 * [Sg_1]--[sg_2]>--<v1>.Sum(A1920, LastMonth) + 1.00, 2.00
    2012-02-01 12:00:00 ? 0.3 * <<1>--<v3>.Sum(A1920, LastMonth) + 1.00
)";

struct Mydelegate : public Historydelegate {
    
    /* CipherContext cipherContext; */
    
    void progress(History * index, Unicodes json) {
        Termlog << json << sep;
    }
    
    void subscription(History * index, Unicodes json) {
        _myOutput << "SUBSCRIPTION: " << json << sep;
    }
    
    int passphrase(History * index, Unicodes fingerprint, void
      (^completion)(ditriaconta hash)) {
        
        int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 result=0;
        
        if (Termlog.password(20, 5, 
          ^(bool &stop) { result = -1; }, 
          ^(Ornaments ds) { ditriaconta hash; completion(hash); }
        )) { result = -2; }
        
        return result;
    }
    
    int encrypt(History * index, Unicodes plaintext, void (^completion)
      (𝟽bit₋text ciphertext)) {
       /* Security::encryptString(plaintext, true, &cipherContext, 
         ^(String &block) { completion(block); }); */
        completion(plaintext);
        return 0;
    }
    
    int decrypt(History * index, 𝟽bit₋text ciphertext, void (^completion)
      (𝟽bit₋text plaintext)) {
       /* Security::decryptString(plaintext, true, &cipherContext, 
         ^(String &block) { completion(block); }); */
        completion(ciphertext);
        return 0;
    }
    
    void appendToJournal(ComputationalIndex * index, Unicodes/const char32_t * snippet) {
       Termlog << "JOURNAL: " << snippet << sep;
    } /* a․𝘬․a appendedToJournal, appendToListhead and preserve₍d₎, and not diff/randomaccess. */
    
    enum class Device { textual₋output, ♭radio₋output, 𝟽bit₋radio₋input, 
      𝟾x𝟾₋matrix, unicode₋audio₋output, rendering₋ready₋construction };
    /* rrc is signal/non-signal and carrying convention. Also displayed-when-not-powered. */
    enum class Easy₋on₋the₋eye { yes, no };
    void addDevice(ComputationalIndex * index, String name, String address) {
       Termlog << "DEVICE: " << name << " on " << address << sep;
    }
    
    int resolveSer₋v₋er(ComputationalIndex * index, Unicodes servername, void (^
      completion)(𝟽bit₋text ip)) {
        𝟽bit₋text ip = 𝟽bit₋text { 8+3, "192.128.2.1" };
        completion(ip);
        return 0;
    }
    
    void entered₋network(ComputationalIndex * index, Unicodes augment) {
        Termlog << "NETWORK: " << augment << sep;
    }
};

UNITTEST(UQL_1)
{
    Mydelegate delegate;
    ComputationalIndex complex("test", &delegate);
    
    complex.evaluate("foo.uql", initial);
    
    /*
        The example renders the following answer in temporal eye (clog):
        
        2012-01-01 12:00:00 ! Scheduled 'Create subgraph sg_1'
        2012-01-01 12:00:00 ! Commit
        2012-01-01 12:00:00 ! Scheduled 'Create subgraph sg_2'
        2012-01-01 12:00:00 ! Commit
        2012-01-01 12:00:00 ! Scheduled 'Create vertex v1'
        2012-01-01 12:00:00 ! Commit
        2012-01-01 12:00:00 ! Scheduled 'Create key A1920 with 0.00, 0.00'
        2012-01-01 12:00:00 ! Commit
        2012-01-01 12:00:00 ! Scheduled '[Sg_1]--[Sg_2]>--<v1>{A1920} = 102.00, 31.12'
        2012-01-01 12:00:00 ! Commit
        2012-01-01 13:00:00 ! Scheduled '>--<v2>{A1920} = 102.00, 31.12' (Note that we're displaying current state or the nudge value here.)
        2012-01-01 12:00:00 ! Commit
        2012-01-01 13:00:00 ! Scheduled 'Attach Detta ser ju jättebra ut!'
        2012-01-01 13:00:00 ! Commit
        
        And the following text on spatial eye (cout):
        
        Snapshot is:
        
        I.e current state was altered in the following way:
        
        2012-01-01 12:00:00 ! 100.32,   200.32 [Sg_1]--[sg_2]>--<v1>{A1920}
        2012-02-01 12:00:00 !  10.00,    20.00 >--<v2>{A1920}
        2012-02-01 13:00:00 !  10.00,    20.00 >--<v2>{A1920}
        
     */
    
    complex.evaluate("foo.uql", update);
    complex.evaluate("foo.uql", query);

    /*
        
        And the following answer on the snapshot view (cout):
        
        2012-01-01 12:00:00 ? 100.32  200.32 = 0.3 * [Sg_1]--[Sg_2]>--<v1>.Sum(A1920, LastMonth) + 1.00, 2.00
        2012-02-01 12:00:00 ?  10.00,  20.00 = 0.3 * <<2>--<v3>.Sum(A1920, LastMonth) + 1.00
        
        Note that the language has an isomorph context dependency as in the 
        creational part. Note that clarity might be improved by the use of two 
        terminals where textual information can be displayed (an isomoph 
        temporal and current view).
        
        The use of breakpoints enable merging of current state and temporal 
        view.
        
     */

    /*
        
        The following format still requires a currentPath initialized to the
        empty string and a prompt while in creational or interactive mode.
        
        Note that only one query is allowed each ts if not prefixed with ?
        
        2012-01-01 12:00:00 ! 100.32   200.32                                       [Sg_1]--[sg_2]>--<v1>{A1920}^102.00, Sum(A1920, LastMonth) + 1.00
        2012-02-01 12:00:00 !  10.00,   20.00                                       [Sg_1]--[sg_2]>--<v2>{A1920}^10.00, 0.20
        2012-02-01 13:00:00 !  10.00,   20.00                                       [Sg_1]--[sg_2]>--<v2>{A1920}^32.32, 200.32 <-- '9bb5ce27-2f74-49c6-bcc3-e1e59c6a83e5'
        2012-01-01 12:00:00 @ (100.32, 110.43, 122.32),  (200.32, 210.32, 222.22)   '9bb5ce27-2f74-49c6-bcc3-e1e59c6a83e5' = Normal(33.32, 0.0) + 1.00, 200.33 // Shows final computation.
        2012-01-01 12:00:00 ? (100.32, 110.43, 122.32),  (200.32, 210.32, 222.22)   0.3 * [Sg_1]--[sg_2]>--<v1>.Sum(A1920, LastMonth) + 1.00
        2012-02-01 12:00:00 ?  10.00,   20.00                                       0.3 * [Sg_1]--[sg_2]>--<v3>.Sum(A1920, LastMonth) + 1.00
        
        Proposed Grammar 
        
        // UQL.ypp -- UQL Grammar. See Table.ypp for multi-thread support.
        
                  uql: (timestamp statement)*
        
            timestamp: [0-9]{4}-[0-9]{2}-[0-9]{2}[ \t\n][0-9]{2}:[0-9]{2}:[0-9]{2}
        
        quoted_string: ' ... '
        
            statement: '!' (graph_path ^ nudge_amount)+
                   |   '@' (quoted_string EQUAL_KEYWORD expression)+
                   |   '?' fully_scoped_expr
                   ;
        
         nudge_amount: fully_scoped_expr | implicitly_scoped_expr
        
           graph_path: ...
        
                 expr: ... (Check for scopeness and strandedness perfomed when in the semantic phase.)
     */

}
