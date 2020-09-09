#pragma once

// 以下宏定義要求的最低平颱。要求的最低平颱
// 是具有運行應用程序所需功能的 Windows、Internet Explorer 等産品的
// 最早版本。通過在指定版本及更低版本的平颱上啓用所有可用的功能，宏可以
// 正常工作。

// 如果必須要針對低於以下指定版本的平颱，請修改下列定義。
// 有關不同平颱對應值的最新信息，請參考 MSDN。
#ifndef _WIN32_WINNT            // 指定要求的最低平颱是 Windows Vista。
#define _WIN32_WINNT 0x0600     // 將此值更改為相應的值，以適用於 Windows 的其他版本。
#endif

