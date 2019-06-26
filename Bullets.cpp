#include "Bullets.h"
#include"PlanetSurface.h"


Bullets::Bullets() {
	head = NULL;
}


void Bullets::addBullets(int x, int y) {
	if (head == NULL) {
		head = new BulletsList;
		head->xBullet = x;
		head->yBullet = y;
		head->eliminato = false;
		head->next = NULL;
	}
	else {
		ptr_BulletsList tmp = head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new BulletsList;
		tmp->next->eliminato = false;
		tmp = tmp->next;
		tmp->xBullet = x;
		tmp->yBullet = y;
		tmp->next = NULL;
	}
}

ptr_BulletsList Bullets::deleteBullets(ptr_BulletsList tmp) {
	if (tmp == NULL)
		return NULL;

	else if (tmp->eliminato == true) {
		ptr_BulletsList p = tmp;
		tmp = tmp->next;
		delete p;
		return deleteBullets(tmp);
	}

	else {
		tmp->next = deleteBullets(tmp->next);
		return tmp;
	}
}

void Bullets::refresh(Spaceship& p,ptr_PlanetSurface planet, int Xinc, int Yinc) {
		
		bool g = false;
		int xx = 0;
		int yy = 0;
		ptr_listaBunker1& head1 = planet->ritornoBunkerList1();
		ptr_listaBunker2& head2 = planet->ritornoBunkerList2();

		ptr_BulletsList tmp = head;

		while (tmp != NULL) {
			planet->impostaMappa(tmp->xBullet, tmp->yBullet, ' ');
			tmp->xBullet += Xinc;
			tmp->yBullet += Yinc;
			if ((planet->ritornaValoreMappa(tmp->xBullet, tmp->yBullet) == ' ' || planet->ritornaValoreMappa(tmp->xBullet, tmp->yBullet) == '.') && planet->ritornaValoreMappa(tmp->xBullet, tmp->yBullet) != 'Y') {
				planet->impostaMappa(tmp->xBullet, tmp->yBullet, '.');
			}
			else if (planet->ritornaValoreMappa(tmp->xBullet, tmp->yBullet) == 'Y') {
				p.lifeMinus();
			}
			else if (planet->ritornaValoreMappa(tmp->xBullet, tmp->yBullet) == 'b') {
				ptr_listaBunker1 tmp1 = head1;
				while ((tmp1->b1->coordinateBunker1(true) != tmp->xBullet) && (tmp1->b1->coordinateBunker1(false) != tmp->yBullet))
					tmp1 = tmp1->next;

				tmp->eliminato = true;
				tmp1->b1->minusLife();
				xx = head->xBullet;
				yy = head->yBullet;
			}
			else if (planet->ritornaValoreMappa(tmp->xBullet, tmp->yBullet) == 'B') {
				ptr_listaBunker2 tmp2 = head2;
				while ((tmp2->b2->coordinateBunker2(true) != tmp->xBullet) && (tmp2->b2->coordinateBunker2(false) != tmp->yBullet))
					tmp2 = tmp2->next;

				head->eliminato = true;
				tmp2->b2->minusLife();
				xx = tmp->xBullet;
				yy = tmp->yBullet;
			}

			else tmp->eliminato = true;
			tmp = tmp->next;
		}
	
		head = deleteBullets(head);
		head1 = modificaLista1(head1, xx, yy, planet);
		head2 = modificaLista2(head2, xx, yy, planet);

}



ptr_listaBunker1 Bullets::modificaLista1(ptr_listaBunker1 &head, int x, int y, ptr_PlanetSurface planet) {
	if (head == NULL) return NULL;
	else if (head->next == NULL) {
		if (head->b1->returnLife() < 1) {
			ptr_listaBunker1 tmp = head;
			planet->impostaMappa(x, y, ' ');
			delete tmp;

			return NULL;
		}
		else return head;
	}
	else if (head->next != NULL) {
		ptr_listaBunker1 tmpOld, tmp1, tmp2;
		tmpOld = head;
		tmp1 = head;
		tmp2 = head->next;
		while (tmp2 != NULL) {
			if (tmp2->b1->returnLife() < 1) {
				ptr_listaBunker1 tmp = tmp2;
				tmp2 = tmp2->next;
				tmp1->next = tmp2;
				planet->impostaMappa(x, y, ' ');
				delete tmp;
			}
			else {
				tmp1 = tmp2;
				tmp2 = tmp2->next;
			}
		}
		if (tmpOld->b1->returnLife() < 1) {
			ptr_listaBunker1 tmp = tmpOld;
			if (tmpOld->next == NULL) {
				tmpOld = NULL;
				planet->impostaMappa(x, y, ' ');
				delete tmp;
			}
			else {
				tmpOld = tmpOld->next;
				planet->impostaMappa(x, y, ' ');
				delete tmp;
			}
		}
		return tmpOld;
	}
}


ptr_listaBunker2 Bullets::modificaLista2(ptr_listaBunker2 &head, int x, int y, ptr_PlanetSurface planet) {
	if (head == NULL) return NULL;
	else if (head->next == NULL) {
		if (head->b2->returnLife() < 1) {
			ptr_listaBunker2 tmp = head;
			planet->impostaMappa(x, y, ' ');
			delete tmp;

			return NULL;
		}
		else return head;
	}
	else if (head->next != NULL) {
		ptr_listaBunker2 tmpOld, tmp1, tmp2;
		tmpOld = head;
		tmp1 = head;
		tmp2 = head->next;
		while (tmp2 != NULL) {
			if (tmp2->b2->returnLife() < 1) {
				ptr_listaBunker2 tmp = tmp2;
				tmp2 = tmp2->next;
				tmp1->next = tmp2;
				planet->impostaMappa(x, y, ' ');
				delete tmp;
			}
			else {
				tmp1 = tmp2;
				tmp2 = tmp2->next;
			}
		}
		if (tmpOld->b2->returnLife() < 1) {
			ptr_listaBunker2 tmp = tmpOld;
			if (tmpOld->next == NULL) {
				tmpOld = NULL;
				planet->impostaMappa(x, y, ' ');
				delete tmp;
			}
			else {
				tmpOld = tmpOld->next;
				planet->impostaMappa(x, y, ' ');
				delete tmp;
			}
		}
		return tmpOld;
	}
}

ptr_BulletsList Bullets::returnList() {
	return head;
}

void Bullets::setList(ptr_BulletsList p) {
	head = p;
}