# Member 06: Search & Filtering Algorithm Engine

## 👤 Member Information
- **Name / Assignee:** Member 06
- **Role:** Search Algorithms & Multi-Field Query Ranking
- **Files Owned:** `SearchEngine.hpp`, `SearchEngine.cpp`
- **Core Technology:** C++17, Algorithms (`<algorithm>`), Custom Sorting Lambdas

---

## 🎯 Contribution Overview
Member 06 implemented the **Search Algorithm & Ranking Engine**:
1. **Multi-Field Relevance Scoring**:
   - Scores each pin based on where query matches occur:
     - Exact Title match: **+10 points**
     - Tag match: **+6 points**
     - Board title match: **+5 points**
     - Category match: **+4 points**
     - Author name/handle: **+3 points**
     - Description text: **+2 points**
2. **Relevance Ranking (`std::sort`)**:
   - Uses `std::sort` with a custom lambda comparator to sort search results in descending order of relevance score.
3. **Category Filtering**:
   - Filters pins by creative discipline (`architecture`, `art-design`, `nature`, `tech`, `fashion`, `food`, etc.).
4. **Combined Filtering**:
   - `searchCombined(pins, category, query)` seamlessly applies category constraints first and then runs relevance search.

---

## 💻 Key Methods
- `SearchEngine::calculateRelevanceScore(pin, query)`: Computes weighted integer score.
- `SearchEngine::search(pins, query)`: Filters and sorts pins by relevance.
- `SearchEngine::filterByCategory(pins, category)`: Filters pins by category.
- `SearchEngine::searchCombined(pins, category, query)`: Combined query pipeline.

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: How does your relevance scoring algorithm work?**  
  *Answer:* It inspects multiple attributes of each `Pin` object against the search term in a case-insensitive manner using `Utils::containsIgnoreCase()`. Different fields have different weights: title matches receive 10 points, tag matches 6 points, down to description matches at 2 points.
- **Q2: What is a C++ lambda expression and how did you use it in `std::sort`?**  
  *Answer:* A lambda expression is an anonymous function object defined inline. We used:
  ```cpp
  std::sort(scored.begin(), scored.end(), [](const auto& a, const auto& b) {
      return a.first > b.first; // sorts highest score first
  });
  ```
- **Q3: What is the time complexity of the search and sort algorithm?**  
  *Answer:* Calculating scores for $N$ pins takes $O(N \cdot M)$ where $M$ is string length. Sorting the $K$ matched results with `std::sort` (Introsort) takes $O(K \log K)$ time.
