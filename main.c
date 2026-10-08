#include <stdio.h>

struct UserAccount {
    int user_id;
    char account_name[31];
    int plan_type;       // 1: Free, 2: Individual, 3: Family
    int active_devices;
    int max_devices;
    int days_overdue;
    int account_status;  // 1: Active, 0: Downgraded
};

int main() {
    struct UserAccount user_list[50];
    int n, i;
    int downgraded_count = 0;
    int device_violation_count = 0;

    // Nhập số lượng tài khoản (1 - 50)
    do {
        printf("Nhap so luong tai khoan can ra soat (1 - 50): ");
        scanf("%d", &n);
        if (n < 1 || n > 50) {
            printf("[LOI] So luong tai khoan khong hop le! Vui long nhap lai.\n");
        }
    } while (n < 1 || n > 50);

    // Nhập thông tin chi tiết từng tài khoản
    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan %d ---\n", i + 1);
        printf("Ma tai khoan (ID): ");
        scanf("%d", &user_list[i].user_id);

        printf("Ten tai khoan / Email: ");
        scanf("%s", user_list[i].account_name);

        do {
            printf("Hang goi hien tai (1: Free, 2: Individual, 3: Family): ");
            scanf("%d", &user_list[i].plan_type);
            if (user_list[i].plan_type < 1 || user_list[i].plan_type > 3) {
                printf("[LOI] Goi dich vu phai thuoc [1, 3]! Nhap lai.\n");
            }
        } while (user_list[i].plan_type < 1 || user_list[i].plan_type > 3);

        do {
            printf("So thiet bi dang ket noi: ");
            scanf("%d", &user_list[i].active_devices);
            if (user_list[i].active_devices < 0) {
                printf("[LOI] So thiet bi khong duoc am! Nhap lai.\n");
            }
        } while (user_list[i].active_devices < 0);

        do {
            printf("So ngay no cuoc gia han: ");
            scanf("%d", &user_list[i].days_overdue);
            if (user_list[i].days_overdue < 0) {
                printf("[LOI] So ngay no cuoc khong duoc am! Nhap lai.\n");
            }
        } while (user_list[i].days_overdue < 0);
    }

    // Khối xử lý quy tắc nghiệp vụ (Business Rules Engine)
    for (i = 0; i < n; i++) {
        // Mặc định trạng thái Active
        user_list[i].account_status = 1;

        // Quy tắc 1: Cập nhật max_devices mặc định
        if (user_list[i].plan_type == 1) {
            user_list[i].max_devices = 1;
        } else if (user_list[i].plan_type == 2) {
            user_list[i].max_devices = 1;
        } else if (user_list[i].plan_type == 3) {
            user_list[i].max_devices = 5;
        }

        // Quy tắc 2: Tự động hạ cấp do nợ cước quá 3 ngày
        if (user_list[i].days_overdue > 3) {
            user_list[i].plan_type = 1;      // Hạ về Free
            user_list[i].max_devices = 1;    // Giới hạn 1 thiết bị
            user_list[i].account_status = 0; // Đánh dấu Downgraded
            downgraded_count++;
        }

        // Quy tắc 3: Cảnh báo vi phạm giới hạn thiết bị
        if (user_list[i].active_devices > user_list[i].max_devices) {
            device_violation_count++;
        }
    }

    printf("\n=======================================================================================\n");
    printf("                  STREAMFLIX - BAO CAO RA SOAT SUBSCRIPTION                            \n");
    printf("=======================================================================================\n");
    printf("%-8s %-20s %-15s %-5s/%-6s %-10s %-12s %-10s\n", 
           "ID TK", "TEN TAI KHOAN", "GOI GOI", "DUNG", "TOI DA", "NO (NGAY)", "TRANG THAI", "CANH BAO");
    printf("---------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-8d %-20s ", user_list[i].user_id, user_list[i].account_name);

        if (user_list[i].plan_type == 1) {
            printf("%-15s ", "Free");
        } else if (user_list[i].plan_type == 2) {
            printf("%-15s ", "Individual");
        } else {
            printf("%-15s ", "Family");
        }

        printf("%-5d/%-6d ", user_list[i].active_devices, user_list[i].max_devices);

        printf("%-10d %-12s ", 
               user_list[i].days_overdue, 
               user_list[i].account_status ? "Active" : "Downgraded");

        if (user_list[i].active_devices > user_list[i].max_devices) {
            printf("%-10s\n", "VI PHAM");
        } else {
            printf("%-10s\n", "OK");
        }
    }

    printf("---------------------------------------------------------------------------------------\n");
    printf("BAO CAO THONG KE VAN HANH:\n");
    printf("- Tong so tai khoan da ra soat                    : %d\n", n);
    printf("- So tai khoan bi tu dong ha cap ve Free (> 3 ngay): %d\n", downgraded_count);
    printf("- So tai khoan dang vi pham vuot thiet bi         : %d\n", device_violation_count);
    printf("=======================================================================================\n");

    return 0;
}