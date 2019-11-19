#include <stdio.h>
#include <stdlib.h>
/*
�㷨˼�룺
1.�������ʱ���յ�ַ������˳�������װ��ĵ�һ���ڴ��
���ҵ�����װ���ڴ��У����Ұ��ڲ���Ƭ�ֳ�������µĽ�����������
��û�ҵ������ʧ��
2.��������ʱ������ҵ����ҵ�Ҫ������ҵ�����ڴ��
���ҵ�����״̬��λδ���䣬��ʱ����ǰ���п��Ժϲ��Ŀ��ڴ����ϲ�
��û���ҵ����򷵻�û���ҵ�����ҵ��Ϣ
*/
//ʹ����������ݽṹ
typedef struct LNode{
	int address;//��ʾ�÷�������ʼ��ַ
	int length; //��ʾ�÷����ĳ���
	int state;  //0��ʾ�÷������У�1��ʾ�÷����ѷ���
	int number; //��ҵ�ı��
	struct LNode *next;
}*pLNode;
//����Ĳ������

//L�������ͷָ�룬addr�Ǹ��ڴ����׵�ַ��len�Ǹ��ڴ��ĳ���
//sta���ڴ���״̬��num�ǽ�ռ���ڴ����ҵ�ı��
void InsertLNode(pLNode L,int addr,int len,int sta,int num) {
	pLNode p = (pLNode)malloc(sizeof(LNode));
	p->address = addr;
	p->length = len;
	p->state = sta;
	p->number = num;
	p->next = NULL;
	L->next = p;
}
//��ʼ������
//��ʼ�������ͷָ�룬�������ϵͳ��8M���ڴ�ռ䣬��ʼַΪ0
//lengΪ�ڴ�ռ���ܴ�С����λΪM
void InitLNode(pLNode L,int leng){
	//L = (pLNode)malloc(sizeof(LNode));
	L->address = 0;//���׵�ַ��ʼ
	L->length = 8;
	L->state = 1;
	L->number = 65535;
	//����ʣ��Ŀ��з���
	InsertLNode(L, 8, leng - 8,0,0);
	printf("��ʼ���ɹ���\n");
}
//������ҵ
//LΪ����ͷָ�룬numΪ����������ҵ���
//���ҵ�����ҵ�����ռ�е��ڴ��state��0
void Revocation(pLNode L, int num) {
	pLNode p = L->next;
	if (p->number == num) {
		//�ҵ��������ҵ
		p->state = 0;
		printf("�ɹ��������Ϊ%d����ҵ��\n",num);
		return;
	}
	while (p->next != NULL) {
		p = p->next;
		p->state = 0;
		printf("�ɹ��������Ϊ%d����ҵ��\n", num);
		return;
	}
	printf("������ҵʧ�ܣ�û���ҵ����Ϊ%d����ҵ\n", num);
}
 //����������Ƿ���������δ�����ڴ���������оͺϲ�

void Merge_free(pLNode L) {
	pLNode p = L,pre;
	int num = 0;//���ڼ�����������ڴ�ռ�����������2��ʾ���������ڴ�ռ�
	while (p != NULL) {
		if (p->state == 0) {
			//��ʾΪ������
			num++;
			if (num == 1)
				pre = p;//Ϊ�ϲ���׼��
			else if (num == 2) {
				//��ʾ�������Ŀ�������ִ�кϲ�����
				//��p���ĳ��ȼӸ�ǰ�����ĳ���
				//ǰ�����ָ��p�����½��
				//�ͷ�p���
				//��pָ��ǰ����㣬�����´��ж�
				//num��1
				pre->length += p->length;
				pre->next = p->next;
				free(p);
				p = pre;
				num = 1;
			}
		}
		else if (p->state == 1)
			num = 0;
		p = p->next;
	}
}
//Ϊ��ҵ�����ڴ�ռ�
//LΪ����ͷָ�룬lenΪ��ҵ��Ҫ���ڴ��С��numΪ��ҵ���
void Allocation(pLNode L, int len, int num) {
	pLNode p = L->next;
	while (p != NULL) {
		if (p->state == 0) {
			//��ʾ�ڴ��δ����
			if (p->length > len) {
				//��ʾ���Է����ڴ�ռ�
				//������Ҫ���ڲ���Ƭ�ֳ����������µĿ����ڴ��
				//�µ��ڴ�����ʼ��ַΪp->address + len������Ϊp->length-len
				pLNode l = (pLNode)malloc(sizeof(LNode));
				l->length = p->length - len;
				l->address = p->address + len;
				l->state = 0;

				l->number = 0;
				l->next = p->next;
				p->next = l;
				p->length = len;
				p->number = num;
				p->state = 1;
				printf("�ڴ����ɹ���\n");
				return;
			}
			else if (p->length == len) {
				//�ոպù����䣬ֻҪ�޸���ҵ��ź��ڴ��״̬����
				p->number = num;
				p->state = 1;
				printf("�ڴ����ɹ���\n");
				return;
			}
		}
		p = p->next;
	}
	printf("�ڴ����ʧ�ܣ�û���ҵ����ʵĿ����ڴ��\n");
}
//��ӡ
void print(pLNode L) {
	printf("************************************************************\n");
	printf("�ڴ����������£�\n");
	printf("��ʼ��ַ\t�ڴ�鳤��\t�����ҵ���\t�ڴ��״̬\n");
	pLNode p = L;
	while (p != NULL) {
		printf("%8d\t%10d\t", p->address, p->length);
		if (p->number == 65535) {
			printf("    ����ϵͳ\t");
		}
		else if (p->number == 0) {
			printf("      ����ҵ\t");
		}
		else {
			printf("%12d\t", p->number);
		}
		if (p->state == 0) {
			printf("      ����\n");
		}
		else {
			printf("    �ѷ���\n");
		}
		p = p->next;
	}
	printf("************************************************************\n");
}
//����ѡ��˵�
int select() {
	int a;
	printf("************************************************************\n");
	printf("��ѡ�����\n");
	printf("1.Ϊ����ҵ�����ڴ�\t2.������ҵ\n3.�鿴�ڴ�������\t4.�˳�\n");
	printf("����������ѡ��");
	scanf("%d", &a);
	return a;
	printf("************************************************************\n");
}
int main()
{
	pLNode L = (pLNode)malloc(sizeof(LNode));
	InitLNode(L, 512);
	int a;
	int len, num;
	a = select();
	getchar();
	while (a != 4) {
		switch (a) {
		case 1:
			printf("������Ҫ�����ڴ����ҵ�ĳ��Ⱥͱ�ţ�");
			scanf("%d%d", &len, &num);
			Allocation(L, len, num);
			break;
		case 2:
			printf("������Ҫ������ҵ�ı�ţ�");
			scanf("%d", &num);
			Revocation(L, num);
			break;
		case 3:
			//system("cls");
			print(L);
			break;
		default:
			break;
		}
		a = select();
	}
    return 0;
}