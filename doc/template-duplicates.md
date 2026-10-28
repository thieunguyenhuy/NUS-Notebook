# Các template chồng lặp chức năng

Rà soát ngày 2026-10-28. Đây là danh sách đề xuất để chủ repo tự chọn xóa;
chưa xóa template nào. Đã đối chiếu các file đang tồn tại và các `#include`
trong `content/`. Việc xóa file vẫn cần cập nhật chapter và stress test liên quan.

Không tìm thấy hai implementation không rỗng giống hệt nhau sau khi bỏ comment
và khoảng trắng. Những nhóm dưới đây là cùng chức năng hoặc các biến thể, không
phải tất cả đều có thể thay thế nguyên trạng cho nhau.

## Ưu tiên cân nhắc để notebook gọn hơn

| Có thể bỏ | Giữ lại / điều kiện | Khác biệt cần biết |
|---|---|---|
| `content/math/FastFourierTransform.h` | Giữ `content/numerical/FastFourierTransform.h` và `FastFourierTransformMod.h` | Bản math dùng long double và trả số nguyên modulo sau khi làm tròn. Bản numerical là FFT/convolution tổng quát, được FFTMod include. Không được xóa FFT numerical nếu vẫn giữ FFTMod. |
| `content/math/GaussElimination.h` | Giữ `content/numerical/SolveLinear.h` | Cùng giải hệ số thực; API khác. Bản math nhận ma trận mở rộng và trả 0/1/2; bản numerical nhận A, b riêng, dùng full pivot và trả rank hoặc -1. `SolveLinear2.h` là hướng dẫn mở rộng của bản numerical. |
| `content/numerical/SolveLinearBinary.h` | Giữ `content/math/GaussElimination2.h` nếu cần cả basis không gian nghiệm | Cùng giải hệ GF(2). Bản math có `get_basis()`, bản numerical có API A/b riêng và trả một nghiệm. Không xóa cả hai. |
| `content/graph/Dinic.h` | Giữ `content/graph/MaxFlow.h` nếu quen API của bạn | Đều là Dinic. Bản Dinic.h có capacity scaling, `addEdge/calc`, reverse capacity và API min-cut khác; MaxFlow.h dùng `add/maxFlow/minCut`. Không thay thế bằng đổi tên file đơn thuần. |
| `content/graph/EdmondsKarp.h` | Giữ ít nhất một trong MaxFlow.h, Dinic.h hoặc PushRelabel.h | Là một cách giải max-flow khác, thường có thể bỏ nếu đã có Dinic. Phù hợp nếu bạn vẫn muốn một implementation ngắn, dễ kiểm chứng cho đồ thị nhỏ. |
| `content/graph/DFSMatching.h` | Giữ `content/graph/BipartieMatching.h` | Cùng matching hai phía; bản DFS đơn giản còn bản class hỗ trợ cover/independent set. `MinimumVertexCover.h` từng include DFSMatching nhưng hiện đã bị bạn xóa. |
| `content/geometry/Geometry.h` | Giữ `Point.h` và các helper geometry chuyên biệt | Geometry.h gộp point/line/distance/intersection/area bằng double; nhiều chức năng đã có trong helper riêng. API và cách xử lý suy biến không hoàn toàn giống nhau. Không header hiện tại nào include Geometry.h. |
| `content/number-theory/Eratosthenes.h` | Giữ `content/number-theory/FastEratosthenes.h` nếu ưu tiên một sieve | Cùng sinh primes; bản đơn giản nhận lim khi gọi, bản fast dùng LIM cấu hình trước. Bitset/API khác nhau. |

## Những nhóm chỉ nên chọn sau khi xem dependency

- **Miller–Rabin:** `math/MillerRabin.h` và `number-theory/MillerRabin.h` cùng bài
  toán. Bản math độc lập, dùng `__uint128_t`; bản number-theory được
  `PollardRho.h` include. Chưa nên xóa bản number-theory nếu chưa sửa PollardRho
  sang API còn lại. `ModMul.h` mà hai file number-theory cần hiện đã bị xóa.
- **Delaunay:** `geometry/DelaunayTriangulation.h` và `geometry/FastDelaunay.h`
  cùng xây dựng triangulation nhưng thuật toán, kiểu dữ liệu và API khác nhau.
  Bản thứ nhất phụ thuộc `3dHull.h`. Chọn một bản dựa trên API bạn muốn dùng;
  không coi chúng là hai file giống hệt nhau.
- **Max-flow:** PushRelabel.h cũng cùng đầu ra max-flow với nhóm trên nhưng là
  thuật toán khác. GomoryHu.h từng cần nó nhưng hiện đã bị xóa. Có thể giữ làm
  biến thể hiệu năng hoặc chỉ giữ một max-flow quen dùng.
- **Lazy segment tree:** LazySegmentTree.h và SegmentTreeLazyIterative.h cùng
  khung range update/query nhưng bản đầu có sẵn add/set/max, bản sau cần định
  nghĩa TT/UT/UU. Có thể chọn một, nhưng không tương đương về API.
- **Ghi chú toán:** Derangements, Catalan và Stirling loại 2 xuất hiện trong cả
  `math/chapter.tex` và `combinatorial/chapter.tex`. Có thể giữ một bản ghi chú.

## Không nên coi là trùng

- Treap theo giá trị khác implicit treap / implicit splay theo vị trí.
- Segment tree thường khác persistent, persistent lazy và time segment tree.
- CHT slopes đơn điệu khác Li Chao có thể thêm slope bất kỳ.
- FFT, FFTMod, NTT và subset transform có điều kiện và phép convolution khác nhau.
- Định thức/inverse trên số thực khác modulo; binary Gauss khác Gauss số thực.
- Suffix array, suffix automaton, suffix tree, Aho–Corasick và palindromic tree
  phục vụ các truy vấn khác nhau.

## Dependency đang thiếu sau các lần xóa file

Đây không phải các file đã được sửa trong lần chỉnh hình; ghi lại để bạn tránh
xóa thêm mà không biết phụ thuộc:

- CompressTree.h -> LCA.h (đã xóa).
- DirectedMST.h -> UnionFindRollback.h (đã xóa).
- number-theory/MillerRabin.h, PollardRho.h -> ModMul.h (đã xóa).
- BerlekampMassey.h, MatrixInverse-mod.h -> ModPow.h (đã xóa).

## Định dạng hình đã chỉnh

- Mỗi hình geometry xuất hiện một lần trong Description của header tương ứng.
- Bỏ tám hình geometry chèn lại nguyên chiều rộng cột ở chapter.tex.
- Thay minipage 75mm/15mm và vspace âm bằng macro `\kactlillustration`.
- Mặc định hình rộng tối đa 38% chiều rộng cột, cao tối đa 12% text height,
  giữ tỉ lệ và không dùng figure float.
- Các ảnh công thức ở math giữ chiều rộng riêng cho dễ đọc, thêm giới hạn chiều
  cao; hình sphericalCoordinates thu nhỏ theo cột.
- `\raggedcolumns` tránh kéo giãn khoảng cách giữa các listing để căn đều đáy.
- Coverage checker theo dõi cả hình được gọi từ Description trong header.
- Bỏ tám import graph còn sót sau các file vừa bị xóa. Không xóa thêm file nào.

Kiểm tra: 12 chapter, 128 listings, mọi hình có tham chiếu; tám header minh họa
preprocess thành công, mỗi hình một lần, phần C++ sau comment đầu file không đổi.
Không compile hoặc thay PDF trong lần này; cần build lại để xem bố cục thực tế.
SoCLaaS đã được thử nhưng endpoint không truy cập được do lỗi DNS.
