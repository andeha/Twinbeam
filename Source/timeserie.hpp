/*  timeserie.hpp | for interpolatives and extrapolatives. */

typedef __builtin_int_t version₋ts;

enum class Operation { create, update, delta, remove };

/**  Records time-varying content and presents current state in O(1). */

template <typename Key, typename Value, typename Reference>
struct Timeserie {
    
    using Temporal = Tuple<Key, Value, version₋ts, version₋ts>; /* ⬷ for certains 'struct' appears clearer. */
    using Event = Tuple<__builtin_int_t, __builtin_int_t>; /* ⬷ todo: extend the
      following typedef to <int, tuple> to support the temporal join operator. */
    using VersionEventIndexPair = Tuple<version₋ts, __builtin_int_t>;
    using PendingChange = Tuple<Operation, Key, Opt<const Value>, Reference>;
    
    explicit Timeserie(version₋ts& Revision) noexcept;
    
    ~Timeserie();
    
#pragma mark reversible-before-commit events
    
    int create(Key key, Value value, Reference valueId);
    int update(Key key, Value value, Reference valueId);
    Opt<const Value> delta(Key key, Value value, Reference
      valueId, void * ctx, Value (^relative)(const Value& l, const Value& r,
      void *ctx)); /* ⬷ changes to either 'Value' becomes one-way here. */
    int remove(Key key);
    
    bool commit(void (^nonePossiblyMany)(Reference ref, const Value& value, 
     version₋ts revision));
    
    void rollback();
    
#pragma mark corrective API
    
    typedef void (^Delta)(Value estimate, Chronology::instant t₋actu, Value &answer, 
     Chronology::relative * next𝘖rNULL₋to₋stop);
    
    int uumph(Chronology::relative latency, Chronology::instant t₋focal, 
     void (^delta)(Value estimate, Chronology::instant t₋actu, Value &answer, 
     Chronology::relative * next𝘖r𝖭𝖴𝖫𝖫₋to₋stop));
    
#pragma mark revisions and the 'last' fixative
    
    version₋ts first() const { return earliest; } /* when empty: first != last */
    
    Opt<version₋ts> last() const { if (earliest != version) { return Opt<version₋ts>(version - 1); } else return Opt<version₋ts>::no(); }
    
    version₋ts end() const { return version; };
    
#pragma mark actualities and snapshots
    
    void state₋before(int count, Key keys[], version₋ts ordin, void 
     (^eventually)(Key keys[], Value value[], bool optionally₋permanent)) const;
    
    void state₋after(int count, Key keys[], version₋ts ordin, void 
     (^eventually)(Key key[], Value value[], bool optionally₋permanent)) const;
    
    template <typename T> struct interval { T beginn, end; };
    /* +-: closed₋beginning, closed₋end. */
    /* unsigned: closed₋beginning, closed₋alt₋open₋end. */
    
    void changes(int count, Key keys[], const interval<version₋ts>& 
     interval, bool closed₋ending, void (^alterificate)(Map<Key, 
     Value> key, bool first, bool last, version₋ts ordin)) const;
    
    /* void addVersion(const Key& forKey, version version); */
    
    const Value& performUpdate(const Key& key, const Value& value);
    
    void performRemove(const Key& key);
    
    void (^pendingchanges_clear)();
    void (^noncommits_clear)();
    
    ˢConvoj<PendingChange> pendingchanges;
    
    void * currents; /* ⬷ a․𝘬․a Map<Key,Value> currents and 'committed current values'. */
    
    void * noncommits; /* ⬷ a․𝘬․a Map<Key,Value> noncommits and 'non-committed-and-possibly-overriding values'. */
    
    enum {
      kVersionNonInactivated = BUILTIN₋INT₋MAX, /* ⬷ indicates a non-inactivated 
    tuple in the temporal table, ⁱ․𝘦 the currently active tuple. */
      kNoCheckpointExists = BUILTIN₋INT₋MAX - 1 
      /* ⬷ the 'nearestCheckpoint' could not find a checkpoint. */
    };
    
    enum { checkpointModulus=2, kActivationEvent=1, kInvalidationEvent=0 };
    
    ˢKnots𝟷ᵈ<Tuple<version₋ts, structure>> checkpoints; /* ⬷ a version plus a dynamic bitset. */
    
    ˢKnots𝟷ᵈ<VersionEventIndexPair> versions; /* ⬷ tracks the sequence of events that 
 are seen by every commit consituting a transaction. */
    
    ˢKnots𝟷ᵈ<Event> events; /* ⬷ tracks the invalidation='0' and activation='1' events. */
    
    ˢKnots𝟷ᵈ<Temporal> temporals; /* ⬷ records 'transaction time' and alterificate. */
    
    version₋ts version; /* ⬷ the version to be committed. */
    
    version₋ts earliest; /* ⬷ cached-copy of the first version ever created. */
    
#pragma mark inherent memory-mangement
    
    Timeserie() = delete;
    
    Timeserie(const Timeserie& other) = default;
    
};

template <typename Key, typename Value, typename Reference>
Timeserie<Key, Value, Reference>::Timeserie(
    version₋ts& revision
) noexcept : version { revision } { earliest = version; 
    pendingchanges_clear = copy₋block(^{ while (pendingchanges.count())
     pendingchanges.pop(); /* delete , free, ... */});
    noncommits_clear = copy₋block(^{ 
      
      Forall(noncommits, ^(Treeint valkey, bool& stop) {
        /* delete , free, ... */
      });
      
    });
}

template <typename Key, typename Value, typename Reference>
Timeserie<Key, Value, Reference>::~Timeserie()
{
    release₋block(pendingchanges_clear);
    release₋block(noncommits_clear);
}

/* ✁ until ✂️ and store --<shoebox>{timeseries} */
/* ✂️ */




