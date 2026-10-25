#ifndef HEAP_COUNTER_H
#define HEAP_COUNTER_H

namespace heapcounter {

// Numara cate blocuri alocate cu new[] sunt inca "in viata" pe heap.
// Se incrementeaza la fiecare alocare si se decrementeaza la fiecare delete[].
// La finalul programului trebuie sa fie 0, altfel avem o scurgere de memorie.
inline int liveBlocks = 0;

}  // namespace heapcounter

#endif  // HEAP_COUNTER_H
