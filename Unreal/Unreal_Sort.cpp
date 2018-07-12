/**
* TArray提供sort()方法用于对元素排序，
* 可以更改默认的比较算法
*/

StrArr.Sort([](const FString& A, const FString& B) {
    return A.Len() < B.Len();
});
// StrArr == ["!","of","Hello","Brave","World","Tomorrow"]