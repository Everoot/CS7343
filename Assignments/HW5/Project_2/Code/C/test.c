//
// Created by Eve Liang on 4/9/23.
//
//
// Created by Eve Liang on 4/9/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

int ta_teaching_time;   //控制理发速度
int s_visit_time; //控制到店速度
int s_leave_time; //控制离店速度

int chair_num;     //椅子数目 Seat
int ta_num;   //理发师数目 Barber
int student_num; //顾客数目 Customer

sem_t student_sem; //顾客状态，用于唤醒理发师
sem_t ta_sem;   //理发师

sem_t mutex;    //通用互斥锁;顾客和理发师之间互斥,理发师&理发师间互斥(特定临界区的进入互斥);
sem_t s_mutex; //顾客之间互斥(主要保护leaves的互斥访问,确保统计数据的准确性.)
sem_t t_mutex; //理发师之间互斥(主要保护各个理发师对业绩的修改的准确性)(不过对于统计业绩的数组而言似乎不是必须,应为各自理发师进程修改的元素是独立的.)

int i, j, k;
// 计数变量(需要互斥访问)
int working_ta = 0;   //统计理发师状态
int waiting_students = 0; //等待中的顾客数
// 顾客间互斥访问leave
int leave_cnt = 0;              //因没有座位而直接离开的顾客数
int served_cnt = 0;             //统计理发师服务的顾客总数
int ta_serve_cnt[50] = {0}; //统计各个理发师业绩(<=50个理发师)的情况
void msleep(int tms);           //毫秒级别睡眠
void set_useed()
{
    // 获取时间微秒级时间,制作种子
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec + tv.tv_usec);
}
void *TA(void *tid_) //理发师线程
{
    while (1)
    {
        // 得到一个0~upper随机数
        set_useed();
        long tid = (long)tid_;
        /* 不同的锁起到的控制范围&程度和效果有所不同
        不同进程对应的代码需要正确的安排使用相应的锁,才可以正确发挥作用
        得到加锁(获得独占机会)的权利,自己同时也可能被锁(阻塞)*/
        // sem_wait(&working_mutex); // Bnum
        // sem_wait(&mutex); //保护waiting_customers访问的准确性(防止访问期间被修改)//既可以作用于顾客也可以作用于理发师(只要在进程代码中加上对应的锁wait())
        // if (waiting_students == 0)
        // {
        //     //没有顾客待理发的顾客(但是未必没有顾客来店里,可能是有其他理发师接手任务了)，理发师睡觉，等待cus信号
        //     printf("********没有顾客,第 %ld 号理发师睡觉!*********\n", tid);
        //     // 这种case下,的主要任务结束,后续退出区释放锁
        //     sem_post(&mutex);
        //     // sem_post(&working_mutex);
        //     // 剩余区交代任务
        // }
        // sem_post(&ta_sem); // post提醒顾客(有可用的理发师),可以来理发了//可以用于通知顾客,理发结束!
        // printf("理发师 %ld 就绪(等待(下)一个顾客唤醒他,若无顾客将休眠)!\n", tid);
        sem_wait(&student_sem); //等待顾客进店(睡觉)
        printf("\t %ldTA has student now ", tid); //printf("\t⏰@理发师%ld有客人了!\n", tid);

        // if (waiting_students > 0)//可省略(否则要加锁访问准确值)
        {
            sem_wait(&mutex);
            waiting_students--; //修改等待中的顾客的数量(互斥地)
            // 关于空闲椅子数量和等待中顾客数量的计数,只需要选择其中一种进行统计,就可以满足判断
            //统计人数
            // printf("  💇‍♀️理发师%ld开始理发,累计服务人数:%d\n", tid, ta_serve_cnt[tid] + 1);
            printf("TA%ld start teaching, he/she has already service number:%d\n", tid, ta_serve_cnt[tid] + 1);

            // printf("本次理发时间：%d\n",CUT_TIME);
            // printf("\t💻 还在等待理发的顾客数: %d\n", waiting_students);
            printf("\tThe number of waiting students: %d\n", waiting_students);
            sem_post(&mutex); //临界资源waiting_customers访问结束 post释放锁

            /*             模拟理发耗时(该过程可以多个理发师同时进行.)*/
            // printf("理发师 %ld 就绪(若无顾客将休眠)!\n", tid);
            // sem_post(&ta_sem); // post提醒顾客(有可用的理发师),可以来理发了
            // printf("\t试探:请求一个顾客...\n");
            // sem_wait(&student_sem);
            // printf("\t@理发师%ld有客人了!\n", tid);
            set_useed();
            ta_teaching_time = rand() % 1001;
            msleep(ta_teaching_time); //控制理发速度,模拟理发师的效率,程序执行过程与该值密切相关.
            // printf("😁一位顾客理发结束!\n");
            // printf("😁第%d位到店的顾客此时理发结束!\n", current_served_cnt);

            /* 更新服务情况,理发师间的专用互斥锁可以视情况不加 */
            int current_served_cnt; //私有变量,不用担心被其他线程访问导致数据不一致
            sem_wait(&t_mutex);
            served_cnt++;                    //统计此时被服务地总人数+1
            current_served_cnt = served_cnt; //记录当前被服务的人数
            ta_serve_cnt[tid]++;         //该理发师bid的服务人数+1
            sem_post(&t_mutex);
           // printf("✅😁第%d位到店的顾客此时理发结束!\n", current_served_cnt);
           // printf("\t@为该顾客理发耗时%d\n", ta_teaching_time);
            printf("%dth arrived student finishes.\n", current_served_cnt);
            printf("\t asking time is: %d\n", ta_teaching_time);


            // 等待,直到被下一位顾客唤醒理发(如果已知没有人来,理发师开始就阻塞在这里睡觉,直到有customer唤醒)
            // 模拟询问顾客是否继续理发/视察休息室的顾客
        }
        sem_post(&ta_sem); // post提醒顾客(有可用的理发师),可以来理发了//可以用于通知顾客,理发结束!
        // printf("理发师 %ld 就绪(等待(下)一个顾客唤醒他,若无顾客将休眠)!\n", tid);
        printf("TA %ld is waiting, if no students will sleep\n", tid);

    } // while
}

/* 顾客线程 */
void *student(void *sid_)
{
    // 得到[0,20]的随机数(作为休眠毫秒数)//模拟离开耗时
    s_leave_time = rand() % 21;
    long sid = (long)sid_;
    printf(" %ldth students come here\n", sid);
    /* 加锁访问临界资源 */
    sem_wait(&mutex);    // for waiting_students
    sem_wait(&s_mutex); // for leave_cnt 互斥锁(作用在顾客之间,理发师代码中不设置此锁,用于保护leave的正确操作)
    /* 确保对waiting_customers的访问是正确的值
    对leave的修改是正确的 */
    /* 一把互斥锁可以创造同代码的进程的临界区(排外)
    在此临界区内,进程可以互斥的执行若干操作,譬如,可以修改一个或者多个临界资源
    而未必仅仅修改一个共享变量
    所以为信号量命名时,以它要保护的变量来命名过于片面
    基于不同代码的进程想要互斥,需要对同一个信号量进行加锁 ;
    使用不同的互斥锁可以更加灵活和精确的控制同代码的进程的临界区,而不造成多余的互斥等待
    */
    /* 顾客到访时间:可以再创建的时候做控制,也可以在线程内部自己sleep
    本实验采用在创建的时候随机延迟,而在线程内部不做延迟 */
    if (waiting_students == chair_num) //没有空位，顾客离开.
    {
        //统计离开人数
        leave_cnt++;
        //printf("\t💔 没有座位,⛔第 %ld 号顾客离开!离开人数累计达到:%d\n", sid, leave_cnt);
        printf("\t There is no seats, %ldth student leave:%d\n", sid, leave_cnt);
        /* free mutexes */
        sem_post(&s_mutex); //释放leave
        sem_post(&mutex);    //释放waiting
    }
    else
        // waiting_students < SNUM
    {
        //更新/统计等待人数
        waiting_students++;
        //printf("\t第 %ld 号有椅子🆗,坐下等待理发,此时等待理发的顾客数:%d\n", sid, waiting_students);
        printf("\t%ldth student has chair, sit down. The waiting student number is:%d\n", sid, waiting_students);
        //如果是第一位顾客，唤醒理发师，唤醒之后工作到没有顾客为止
        //唤醒理发师
        int student_value;

        // sleep(1);
        // sem_getvalue(&student_sem, &student_value);
        // printf("❤️❤️❤️customer_sem value:%d=======\n", student_value);
        /* free mutexes */
        sem_post(&s_mutex); //释放leave,允许其他顾客进程修改leave
        sem_post(&mutex);    //释放waiting,允许所有其他进程互斥的修改waiting
        // signal the TA(student available)
        sem_post(&student_sem); // post提醒理发师有顾客进店

        // printf("\t🤷‍♂️顾客请求一就绪的位理发师!\n");
        // (或者设计为,等待理发师理发完毕后退出线程),当然这不是sem_wait()的本意
        sem_wait(&ta_sem); //等待理发师(理发师的post(&bar信号)
    }

    msleep(s_leave_time); //非必要语句,控制客人离开速度
}
void msleep(int tms)
{
    struct timeval tv;

    tv.tv_sec = tms / 1000;
    tv.tv_usec = (tms % 1000) * 1000;
    select(0, NULL, NULL, NULL, &tv);
}

int main()
{
    int temp;

    //printf("请输入椅子数目:");
    printf("please input the chairs number:");
    scanf("%d", &chair_num);
    //printf("请输入理发师数目:");
    printf("please input the ta number:");
    scanf("%d", &ta_num);
    printf("please input the students number:");
    scanf("%d", &student_num);

    int res;
    pthread_t ta_thread[ta_num], student_thread[student_num];

    //初始化信号量
    //同步信号量
    sem_init(&ta_sem, 0, 0);   //清醒的理发师数量(初始为0)
    sem_init(&student_sem, 0, 0); //等待理发师的数量(初始为0)
    // 互斥量
    sem_init(&mutex, 0, 1);
    sem_init(&s_mutex, 0, 1);
    sem_init(&t_mutex, 0, 1);

    //创建理指定数量的发师进程
    for (i = 1; i <= ta_num; i++)
    {
        res = pthread_create(&ta_thread[i], NULL, TA, (void *) (long) (i));
        // sleep(1);
        if (res != 0)
            perror("Thread creation failure!\n");
        printf("~~~~~TA%d created!\n", i);
    }

    //创建指定数量的顾客进程
    for (i = 1; i <= student_num; i++)
    {
        // 模拟顾客到来的时间时间线
        // 微秒级别变化的种子,该随机间歇时间间隔模拟可选
        // set_useed();
        // s_visit_time = rand() % 31; //随机时间间隔(0~30)来一个顾客
        // msleep(s_visit_time);

        s_visit_time = rand() % 500000 / 2; //随机时间间隔来一个顾客
        printf("-----@(create)s_visit_time:%d,usleeping...\n", s_visit_time);
        usleep(s_visit_time);
        res = pthread_create(&student_thread[i], NULL, student, (void *) (long) (i));
        if (res != 0)
            perror("Thread creation failure!\n");
        printf("~~~~~student%d created!\n", i);
    }
    for (i = 1; i <= student_num; i++)
    {
        //进程等待所有消费者线程结束
        pthread_join(student_thread[i], NULL);
    }
    //printf("❤️❤️所有顾客分配完毕处理完毕\n");
    printf("All students has scheduled.\n");
    // sleep(1);

    for (j = 1; j <= ta_num; j++)
    {
        //printf("第 %d 号理发师服务人数:%d\n", j, ta_serve_cnt[j]);
        printf("%dth ta service sum of students:%d\n", j, ta_serve_cnt[j]);
    }
    //printf("理发师服务顾客总数:%d\n", served_cnt);
    //printf("直接离开的顾客总数:%d\n", leave_cnt);
    printf("The sum of TA has teaching students:%d\n", served_cnt);
    printf("The sum of leaving students:%d\n", leave_cnt);
    printf("\n");
}
